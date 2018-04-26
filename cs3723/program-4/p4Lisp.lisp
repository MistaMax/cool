;;;
(defmacro diag (diagid &rest ex)
    `(putp ' ,diagid diag-HT ' ,ex ) 
)

(defmacro isa (expr type)
    `(putp ' ,expr isa-HT ' ,type)
)

(defmacro symptom (&rest expr)
    `(COND ((getp ' ,expr isa-HT) (putp ' ,expr symptom-HT ' T) (putp (getp ' ,expr isa-HT) symptom-HT T)) 
        (T (putp ' ,expr symptom-HT ' T))
    )
)

(defun printTree (rootID)
    
)



(defun triage ()

)
