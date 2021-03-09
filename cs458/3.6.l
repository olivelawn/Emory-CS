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
;problem 3-6 F-TO-C and C-TO-F.  makes celcius to farenheight conversions
; and vice versa

;farenheight to celcius
(defun f-to-c (f)
  (- (* (+ 40 f) (/ 5 9)) 40 ) ) )

;sample input
;(f-to-c 32)

;celcius to farenheight
(defun c-to-f (c)  
  (- (* (+ 40 c) (/ 9 5)) 40 ) ) )

;sample input
;(c-to-f 0)


