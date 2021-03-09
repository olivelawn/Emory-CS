;;   ------------------ 5.5.l ------------------
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

;5-5 towers of hanoi

(defun towers-of-hanoi (disks)
  (if (endp disks)
      0
        (+ (towers-of-hanoi (rest disks)) 1 (towers-of-hanoi (rest disks)))))

;sample input:
;(towers-of-hanoi '(1))
;(towers-of-hanoi '(2 1))
;(towers-of-hanoi '(3 2 1))
;(towers-of-hanoi '(4 3 2 1))
;(towers-of-hanoi '(5 4 3 2 1))

