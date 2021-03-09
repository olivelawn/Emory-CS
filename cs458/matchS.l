 ;;------matchS.l-------

 ;;---(1) Question mark, ?, plays a wild card---
 ;;---(1) Star mark, *, plays wild cards---


(defun  matchS  (A B)
   (cond 
      ((null A)  (null B))
      ((or  (atom A)  (atom B))  nil)
      ((equal  (first A)  (first B))
         (matchS  (rest A)  (rest B)))
      ((and 
            (not (atom (first A)))       
            (equal  (length (first A)) 2)
            (eq (caar A)  '?)
            (matchS (cdr A)  (cdr B)))
         (set (cadar  A)  (car B)) T)
      ((and 
            (not (atom (first A)))
            (equal  (length (first A)) 2)
            (eq (caar A)  '*))
         (cond
            ((matchS (cdr A) B)
               (set (cadar A) nil) t)
            ((and A (matchS (rest A) (rest B)))
               (set (cadar A) (list (car B))) t)
            ((and A (matchS A (cdr B)))
               (set (cadar A) (cons (car B) (eval (cadar A))) ) t)
       (t nil))) ))
