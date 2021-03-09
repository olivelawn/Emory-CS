;;   ------------------ 4.3.l ------------------
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

;  RIGHTP 4-3

(defun rightp (num1 num2 num3)  
  (> (* .02 (* num1 num1)) (abs (- (* num1 num1) (+ (* num2 num2) (* num3 num3) )))) )


;sample input:
;(rightp 5 4 3)
;(rightp 5 4 2.99)
;(rightp 5 4 3.01)
;(rightp 5 4 100)

