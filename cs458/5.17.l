;;   ------------------ 5.17.l ------------------
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

;5-17 user-defined-nthcdr

(defun user-defined-nthcdr (n l)
  (if (zerop n) l
  (user-defined-nthcdr (- n 1) (rest l))))

;sample input:
;(user-defined-nthcdr 2 '(A B C D))
;(user-defined-nthcdr 2 '((A B) C D))
;(user-defined-nthcdr 2 '((A B) (C D) E))

