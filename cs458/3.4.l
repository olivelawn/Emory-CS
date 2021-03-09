;;   ------------------ 3.1.l ------------------
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
;problem 3-3 ROTATE-RIGHT.  Takes a list as input and returns a
;new list in which the former last element becomes the first

(defun rotate-right (a)
  (append (last a) (butlast a) ))

;example input
;(setf abc-list '(a b c))
;(rotate-right abc-list)
;(rotate-right '(a b c))
;(rotate-right (rotate-right '(a b c)))



