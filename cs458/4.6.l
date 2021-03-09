;;   ------------------ 4.6.l ------------------
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

(not U):   	(cond (('U) (not U))
	              ((t (T) ))  )	;U is nil therefore T

(or x y z) 	(cond ((or x y z) z)
		      ((t (nil) )) ) ;or failed return nil

(and a b c) 	(cond ((and a b c) c)
		      ((t (nil) )) ) ;and failed return nil
