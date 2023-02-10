(define (domain travessia)
    (:requirements :typing)
    (:types 
            kid adult - person
    father mother officer - adult
            girl boy thief - kid
    )
    (:predicates
        (boatPos1free ?bp1 ?p - person)
        (boatPos2free ?bp1 ?p - person)
        (father ?f - adult)
        (mother ?m - adult)
        (girl ?g - kid)
        (boy ?b - kid)
	    (officer ?o - adult)
	    (thief ?t - kid)
        (crossed ?l ?a - adult)
        (crossed ?l ?c - kid)
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