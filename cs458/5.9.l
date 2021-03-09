;;   ------------------ 5.9.l ------------------
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
;5-9  squash

(defun squash (l)
  (cond ((null l) nil)
        ((atom l) (list l))
        ( t (append (squash (first l))
		    (squash (rest l))))))



;sample input:
;(squash '(a (a (a (a b))) (((a b) b) b) b))
;(squash '(a b c))
;(squash '( ))
;(squash '( (a) (b) (c) (d) ))

