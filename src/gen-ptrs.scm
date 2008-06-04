;;;
;;; gen-ptrs.scm - Generate gl-ptrs.c
;;;
;;;  Copyright (c) 2005-2008  Shiro Kawai  <shiro@acm.org>
;;;
;;;  Redistribution and use in source and binary forms, with or without
;;;  modification, are permitted provided that the following conditions
;;;  are met:
;;;
;;;   1. Redistributions of source code must retain the above copyright
;;;      notice, this list of conditions and the following disclaimer.
;;;
;;;   2. Redistributions in binary form must reproduce the above copyright
;;;      notice, this list of conditions and the following disclaimer in the
;;;      documentation and/or other materials provided with the distribution.
;;;
;;;   3. Neither the name of the authors nor the names of its contributors
;;;      may be used to endorse or promote products derived from this
;;;      software without specific prior written permission.
;;;
;;;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
;;;  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
;;;  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;;;  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
;;;  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
;;;  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
;;;  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
;;;  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
;;;  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
;;;  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
;;;  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;;;
;;;  $Id: gen-ptrs.scm,v 1.5 2008-06-04 11:50:33 shirok Exp $
;;;

(use util.match)
(use gauche.cgen)

(define *glext-abi* "glext-abi.scm")

(cgen-current-unit
 (make <cgen-unit>
   :name "gl-ptrs"
   :c-file "gl-ptrs.h" ;; hack
   :preamble "/* generated by gen-ptrs.scm $Revision: 1.5 $.  DO NOT EDIT */"
   :init-prologue "" ;; we don't use init fn
   :init-epilogue "" ;; ditto
   ))

(define (main args)
  (cgen-decl "#ifndef APIENTRY" "#define APIENTRY  /*empty*/" "#endif"
             "#ifndef APIENTRYP" "#define APIENTRYP APIENTRY*" "#endif"
             "#ifndef GL_VERSION_2_0"
             "typedef char GLchar;"
             "#endif"
             "#ifndef GL_VERSION_1_5"
             "typedef ptrdiff_t GLintptr;"
             "typedef ptrdiff_t GLsizeiptr;"
             "#endif"
             "#ifndef GL_ARB_vertex_buffer_object"
             "typedef ptrdiff_t GLintptrARB;"
             "typedef ptrdiff_t GLsizeiptrARB;"
             "#endif"
             "#ifndef GL_ARB_shader_objects"
             "typedef char GLcharARB;"
             "typedef unsigned int   GLhandleARB;"
             "#endif"
             "#ifndef GL_ARB_half_float_pixel"
             "typedef unsigned short GLhalfARB;"
             "#endif"
             "#ifndef GL_NV_half_float"
             "typedef unsigned short GLhalfNV;"
             "#endif"
             "#define ENSURE(fn) \\"
             "  do{if ((fn) == NULL){\\"
             "      fn = (SCM_CPP_CAT(type__, fn))Scm_GLGetProcAddress(#fn);\\"
             "     }} while (0)"
             )
  (with-input-from-file *glext-abi*
    (cut port-for-each gen read))
  (cgen-emit-c (cgen-current-unit))
  0)

(define (gen expr)
  (match expr
    (('define-entry-point fn typename typedef)
     ;; we won't use typename (PFN.*PROC), for it may be duplicated
     ;; if platform's glext.h is already included.  Also we insert
     ;; #define to add 'ptr_' suffix to the function pointer, to avoid
     ;; possible name conflict.
     (let* ((ptrname #`"ptr__,fn")
            (ourtypename #`"type__,ptrname"))
       (receive (pre post) (string-scan typedef (x->string typename) 'both)
         (when pre
           (cgen-decl #`",|pre|,|ourtypename|,|post|")
           (cgen-decl #`"#define ,fn ,ptrname")
           (cgen-body #`"static ,|ourtypename| ,fn = NULL;")))))
    (else #f)))
