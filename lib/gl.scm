;;;
;;; gl.scm - Gauche GL binding
;;;
;;;  Copyright(C) 2001 by Shiro Kawai (shiro@acm.org)
;;;
;;;  Permission to use, copy, modify, distribute this software and
;;;  accompanying documentation for any purpose is hereby granted,
;;;  provided that existing copyright notices are retained in all
;;;  copies and that this notice is included verbatim in all
;;;  distributions.
;;;  This software is provided as is, without express or implied
;;;  warranty.  In no circumstances the author(s) shall be liable
;;;  for any damages arising out of the use of this software.
;;;
;;;  $Id: gl.scm,v 1.2 2002-09-23 03:39:26 shirok Exp $
;;;

(define-module gl
  (use srfi-4)                          ;uniform vector
  (export-all)
  )
(select-module gl)

(dynamic-load "gauche-gl")

;; utilities

(define-syntax gl-begin*
  (syntax-rules ()
    ((_ mode commands ...)
     (begin
       (gl-begin mode) commands ... (gl-end)))
    ))

(provide "gl")
