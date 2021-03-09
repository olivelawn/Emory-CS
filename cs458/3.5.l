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
;problem 3-5 PALINDROME.  takes in a list of elements and returns
; a palindrome

(defun palindrome (a)
  (append a (reverse a) ))

;sample input
;(palindrome '(h o m e))
;(palindrome '(f o r))
;(palindrome '(a b l e w a s I e r))

