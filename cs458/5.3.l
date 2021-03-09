;;   ------------------ 5.3.l ------------------
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

;5-3 keep-first-n-cleverly and keep-first-n-cleverly-aux

(defun keep-first-n-cleverly (n l)
  (keep-first-n-cleverly-aux n l nil))

(defun keep-first-n-cleverly-aux (n l result)
  (if (zerop n)
	(reverse result)
	(keep-first-n-cleverly-aux (- n 1) (rest l) (cons (first l) result))))

;sample input:
;(keep-first-n-cleverly 3 '(a b c d e f) )
;(keep-first-n-cleverly 0 '(a b c d e f) )
;(keep-first-n-cleverly 10 '(a b c d e f) )
;(keep-first-n-cleverly 1 '(a b c d e f) )

