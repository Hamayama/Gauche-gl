;; Example6-1  Blending Example

(use gl)
(use gl.glut)

(define *left-first* #t)

(define (init)
  (gl-enable |GL_BLEND|)
  (gl-blend-func |GL_SRC_ALPHA| |GL_ONE_MINUS_SRC_ALPHA|)
  (gl-shade-model |GL_FLAT|)
  (gl-clear-color 0.0 0.0 0.0 0.0)
  )

(define (draw-left-triangle)
  (gl-begin |GL_TRIANGLES|)
  (gl-color '#f32(1.0 1.0 0.0 0.75))
  (gl-vertex '#f32(0.1 0.9 0.0))
  (gl-vertex '#f32(0.1 0.1 0.0))
  (gl-vertex '#f32(0.7 0.5 0.0))
  (gl-end))

(define (draw-right-triangle)
  (gl-begin |GL_TRIANGLES|)
  (gl-color '#f32(0.0 1.0 1.0 0.75))
  (gl-vertex '#f32(0.9 0.9 0.0))
  (gl-vertex '#f32(0.3 0.5 0.0))
  (gl-vertex '#f32(0.9 0.1 0.0))
  (gl-end))

(define (disp)
  (gl-clear |GL_COLOR_BUFFER_BIT|)
  (if *left-first*
      (begin (draw-left-triangle)
             (draw-right-triangle))
      (begin (draw-right-triangle)
             (draw-left-triangle)))
  (gl-flush)
  )

(define (reshape w h)
  (gl-viewport 0 0 w h)
  (gl-matrix-mode |GL_PROJECTION|)
  (gl-load-identity)
  (if (<= w h)
      (glu-ortho-2d 0.0 1.0 0.0 (* 1.0 (/ h w)))
      (glu-ortho-2d 0.0 (* 1.0 (/ w h)) 0.0 1.0))
  )

(define (keyboard key x y)
  (cond
   ((or (= key (char->integer #\t))
        (= key (char->integer #\T)))
    (set! *left-first* (not *left-first*))
    (glut-post-redisplay))
   ((= key (char->integer #\escape))
    (exit 0))
   ))

(define (main args)
  (glut-init args)
  (glut-init-display-mode (logior |GLUT_SINGLE| |GLUT_RGB|))
  (glut-init-window-size 200 200)
  (glut-create-window *program-name*)
  (init)
  (glut-reshape-func reshape)
  (glut-keyboard-func keyboard)
  (glut-display-func disp)
  (glut-main-loop)
  0)
