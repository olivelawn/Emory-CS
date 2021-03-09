;;   ------------------ 5.13.l ------------------
;;
;;				created by: parker johnson
;;				date completed: sept 17 4:00 a.m.
;;
;;   HONOR PLEDGE:
;;		    I, parker johnson, pledge that this and confirms
;;		    to SPCA.
;;					parker johnson
;;
;;-------------------------------------------------

;5-13  tail-recursive-expt

(defun tail-recursive-expt (m n &optional (c 1))
  (if (zerop n)
 	c
      (tail-recursive-expt m (- n 1) (* m c)) ) )

;sample input:
;(tail-recursive-expt 2 3)
;(tail-recursive-expt 2 3 4)

;comment:  assumming initial invocation with 2 args
