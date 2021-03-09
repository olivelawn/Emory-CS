;;   ------------------ 6.2.l ------------------
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

; 6-2 my-length program counts # of atoms in an expression

(defun my-length (l &optional (sum 0))
   (cond ((null l) sum)
	 ((atom l) (+ sum 1))
	 (t (my-length (rest l) (my-length (first l) sum )))))

;sample input:
;(my-length '(1 2 3 4) 0)
;(my-length '(sqrt (expt x 2) (expt y 2))))

