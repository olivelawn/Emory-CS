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
;problem 3-3 ROTATE-LEFT.  Takes a list as input and returns a
;new list in which the former first element becomes the last

(defun rotate-left (a)
  (append (rest a) (list (first a) )))

;example input
;(setf abc-list '(a b c))
;(rotate-left abc-list)
;(rotate-left '(a b c))

