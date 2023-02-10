(define (domain travessia)
    (:requirements :typing)
    ; (:types father mother officer - adult
    ;         kid adult - person
    ;         girl boy thief - kid
    ; )
    (:types boat father mother officer girl boy thief left right)
    (:predicates
        ; (boatPos1free ?bp1 ?p - person)
        ; (boatPos2free ?bp1 ?p - person)
        ; (crossed ?l ?a - adult)
        ; (crossed ?l ?c - kid)
	    ; (person ?p - (either father mother officer girl boy thief))
        
        (at ?who - (either father mother officer girl boy thief) ?side - (left right))
        (boat_at ?side - (either left right))
    )

    (:action place-adult-boat-pos1
        :parameters (?a - adult)
        :precondition (and (boatPos1free ?bp1))
        :effect (and not(boatPos1free ?bp1))
    )

    (:action place-adult-boat-pos2
        :parameters (?a - adult)
        :precondition (and (boatPos2free ?bp1))
        :effect (and not(boatPos2free ?bp1))
    )

     (:action place-kid-boat-pos1
        :parameters (?k - kid)
        :precondition (and (boatPos1free ?bp1))
        :effect (and not(boatPos1free ?bp1))
    )

    (:action place-kid-boat-pos2
        :parameters (?k - kid)
        :precondition (and (boatPos1free ?bp1))
        :effect (and not(boatPos1free ?bp1))
    )

    (:action move-boat-adult
        :parameters (?a - adult)
        :precondition (or not (boatPos1free ?bp1))
        :effect (and not(boatPos2free ?bp1))
    )


)