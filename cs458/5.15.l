;;   ------------------ 5.15.l ------------------
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

;5-15  clever-count-atoms

(defun clever-count-atoms (l &optional (sum 0))
   (cond ((null l) sum)
	 ((atom l) (+ sum 1))
	 (t (clever-count-atoms (rest l) (clever-count-atoms (first l) sum )))))

;sample input:
;(clever-count-atoms '(1 2 3 4) 0)
;(clever-count-atoms '(sqrt (expt x 2) (expt y 2))))

