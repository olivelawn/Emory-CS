;;   ------------------ 4.7.l ------------------
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

; CHECK-TEMP  4-7

(defun check-temp (temp)
  (cond ((> temp 100) 'ridiculously-hot)
        ((< temp 0) 'ridiculously-cold)
	(t 'ok)
  )
)

;sample input:
;(check-temp 101)
;(check-temp 50)
;(check-temp -1)

