
 ;;------matchS.l-------

 ;;---(1) See first matchQ.l---
 ;;---(2) This additionally checks property---


(defun  matchS  (A B &optional flag)
  (if (eq flag 0) (setf tmp_list '() ))
   (cond 
      ((null A)  (null B))
      ((or  (atom A)  (atom B)) nil)
      ((equal  (first A)  (first B))
         (matchS  (rest A)  (rest B)))
      ((and 
            (equal  (length (first A)) 2)
            (eq (caar A)  '?)
            (matchS (cdr A)  (cdr B)))
         (set (cadar  A)  (car B)) T)
      ((and 
            (equal  (length (first A)) 2)
            (null (or (eq (caar A)  '?) (eq (caar A)  '*)))
            (apply  (caar A)  (list (car B)))
            (matchS  (cdr A)  (cdr B)))
         (set (cadar A)  (car B)) T)
      ((and 
	    (not (atom (first A)))
	    (equal (length (first A)) 2)
	    (eq (caar A) '*)
 	    (setf tmp_list (append tmp_list (list (first B))))
            (set (cadar A) tmp_list)  
		(cond
		  ((equal (rest A) B) (set (cadar A) nil) (matchS (rest A) B ))
		  ((equal (rest A) (rest B)) (matchS (rest A) (rest B) 1 ))
	          (t
		     (if (equal (cadr A) (cadr B)) (matchS (rest A) (rest B) 0 ) (matchS A (rest B) 1 )) ))
	    	  
	))) )

;sample input:
;case 1:
;(matchS '(a (* x) b c) '(a b c) 0)
;case 2:
;(matchS '(a (* x) c) '(a b c) 0)
;case 3:
;(matchS '(a (* x) b) '(a 1 2 b) 0)
;other stuff:
;(matchS '(a (* x) f) '(a b c d e f) 0 )
;(matchS '(a (* x) b (* y) c) '(a 1 2 3 b 4 5 6 c) 0 )