;;   ------------------ 5.1.l ------------------
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

; 5-1  skip-first-n

(defun skip-first-n (n l)
  (if (zerop n)
	l
	(skip-first-n (- n 1) (rest l) )))


;sample input:
;(skip-first-n 3 '(A B C D E F G H I) )
;(skip-first-n 3 '(A B C l i s p) )
;(skip-first-n 10 '(A B C l i s p) )
;(skip-first-n 0 '(A B C l i s p) )
   
