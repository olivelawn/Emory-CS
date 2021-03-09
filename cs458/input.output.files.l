;-------------------------------<input/output.files.l>-------------------------
;---   (with-open-file (<stream name>
;---                    <file specification>
;---                    <:direction :input
;---                   )
;---            . . . .
;---            . . . .
;---            (read <stream name> nil)
;---            . . . .
;---            . . . .
;---   )
;---
;---   (1) <file specification> may include UNIX path names
;---   (2) if "read <stream name>" fails, it returns "nil" instead of panic
;---



(defun dolist-1 (list-elements)
  (let ( (even 0) (result 0) )
    (dolist (element list-elements result)
      (when (evenp element)
        (setf result (+ result 1))
        (format t "~%~3a~3a" element result)
) ) ) )


(with-open-file (x-stream "./input.data1" :direction :input)
  (dolist-1 (read x-stream))
)


;-------------------------------<input/output.files.l>-------------------------
;---   (with-open-file   (<input-stream name>
;---                      <file specification>
;---                      <:direction :input
;---                     )
;---     (with-open-file (<output-stream name>
;---                      <file specification>
;---                      <:direction :output
;---                     )
;---            . . . .
;---            (read <input-stream name> nil)
;---            . . . .
;---            (print <item> <output-stream name>)
;---            . . . .
;---   )
;---
;---   (1) <file specification> may include UNIX path names
;---   (2) if "read <stream name>" fails, it returns "nil" instead of panic
;---


(with-open-file (y-stream "./output.1" :direction :output)
  (defun dolist-1 (list-elements)
    (let ( (even 0) (result 0) )
      (dolist (element list-elements result)
        (when (evenp element)
          (setf result (+ result 1))
          (format y-stream "~%~3a~3a" element result)
  ) ) ) )

  (dolist-1 '(1 2 3 4 5 6 7 8 9)) 
)
