;;   ------------------ 5.11.l ------------------
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

;5-11  punctuate

(defun punctuate-w-o (l &optional (mark 'period))
   (append l (list mark) ) )

;sample input:
;(punctuate-w-o '(this is an example))
;(punctuate-w-o '(this is an example) 'question-mark)

