;;;
(defmacro diag (diagid &rest ex)
    `(putp ' ,diagid diag-HT  ' ,ex ) 
)

(defmacro isa (expr type)
    `(putp ' ,expr isa-HT  ' ,type)
)

(defmacro symptom (expr)
    `(putp ' ,expr symptom-HT  ' T)
    (NOT (NULL (getp ' ,expr isa-HT)) NIL)
)

(defun printTree (rootID)
    
)



(defun triage ()

)