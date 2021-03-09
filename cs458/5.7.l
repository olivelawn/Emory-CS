;;   ------------------ 5.7.l ------------------
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
;5-7 strange

(defun strange (l)
  (cond ((null l) nil)
        ((atom l) l)
        (t (cons (strange (first l))
		 (strange (rest l))))))

;comment: function strange checks to see if list is empty
; if so it returns nil.  If the list contains a single atom
; it returns that atom.  Otherwise, the list is recusively
; decomposed and put together to replicate the inputed list
