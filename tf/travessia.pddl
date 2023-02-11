(define (domain travessia)
    (:requirements :typing :strips :negative-preconditions :disjunctive-preconditions)
    (:types boat father mother officer girl boy thief left right)
    (:predicates
        (empty_boat ?boat - boat)
        (half_empty_boat ?boat - boat)
        (full_boat ?boat - boat)
        (at ?who - (either father mother officer girl boy thief) ?side - (either left right))
        (boat_at ?side - (either left right))
        (on_boat ?who - (either father mother officer girl boy thief) )
    )
    ;from = left
    ;to = right
    (:action father_move_boat
        :parameters (?from ?to - (either left right) ?father - father )
        :precondition (and  (at ?father ?from)
                            (boat_at ?from)
                            (or (and (at mother ?to) (at boy ?from))
                            ; o thief no from o officer nunca poderá estar no to
                                (and (at officer ?to)  (at thief ?from))
                                (and (on_boat mother)  (at girl ?to))
                                (and (on_boat officer)  (at thief ?to))
                                (and (at mother ?to) (at girl ?to))))
        :effect (and (boat_at ?to)
                     (not (boat_at ?from))
        )
    )

    (:action mother_move_boat
        :parameters (?from ?to - (either left right) ?mother - mother )
        :precondition (and  (at ?mother ?from)
                            (boat_at ?from)
                            (or (and (at father ?to) (at girl ?from))
                                (and (at officer ?to)  (at thief ?from))
                                (and (on_boat father)  (at boy ?to))
                                (and (on_boat officer)  (at thief ?to))
                                (and (at father ?to) (at boy ?to))))
        :effect (and (boat_at ?to)
                     (not (boat_at ?from))
        )
    )

    (:action officer_move_boat
        :parameters (?from ?to - (either left right) ?officer - officer )
        :precondition (and  (at ?officer ?from)
                            (boat_at ?from)
                            (or (and (at father ?to) (at thief ?from))
                                (and (at officer ?to)  (at thief ?from))
                                (and (on_boat father)  ((at boy ?to)))
                                (and (on_boat officer)  (at thief ?to))
                                (and (at father ?to) (at boy ?to))))
        :effect (and (boat_at ?to)
                     (not (boat_at ?from))
        )
    )


;   )
;     (:action farmer_offshore :parameters(?boat - boat)
;    :precondition (and (empty_boat ?boat)
;                       (at wolf southbank)
;                       (at goat southbank)
;                       (at cabbage southbank)
;                       (at farmer southbank)
;                       (at_bank boat southbank))
                      
;    :effect (and (not (empty_boat ?boat))
;                 (half_empty_boat ?boat)
;                 (not (at farmer southbank))
;                 (target_in_boat farmer ?boat))
  
;   )
  
;   (:action farmer_onshore :parameters(?boat - boat)
;    :precondition (and (half_empty_boat ?boat)
;                       (at wolf northbank)
;                       (at goat northbank)
;                       (at cabbage northbank)
;                       (target_in_boat farmer ?boat)
;                       (at_bank boat northbank))
                      
;    :effect (and (empty_boat ?boat)
;                 (not (half_empty_boat ?boat))
;                 (at farmer northbank)
;                 (not (target_in_boat farmer ?boat)))
  
;   )
  
;   (:action move_empty_boat :parameters (?from ?to - (either southbank northbank) ?boat - boat)
;    :precondition (and (at_bank ?boat ?from)
                      
;                       (half_empty_boat ?boat)
;                  )
;    :effect (and (not (at_bank ?boat ?from)) 
                
;                 (at_bank ?boat ?to)
;                 (half_empty_boat ?boat)
;            )
                
;   )
  

;   (:action move :parameters (?from ?to - (either southbank northbank) ?boat - boat)
;    :precondition (and 
;                       (not (empty_boat ?boat))
;                       (at_bank ?boat ?from)
;                       (full_boat ?boat))
;    :effect (and 
;                 (not (at_bank ?boat ?from))
;                 (at_bank ?boat ?to)
;                 (full_boat ?boat)
;             )

;   )
  
;   (:action wolf_on_boat :parameters (?y - (either southbank northbank) ?boat - boat)
;    :precondition (and
;                     (at wolf southbank)
;                     (at goat northbank)
;                     (at cabbage southbank)
;                     (at_bank ?boat southbank)
                    
;                     (at wolf ?y)
;                     (not (target_in_boat wolf ?boat))
;                     (target_in_boat farmer ?boat)
;                     (half_empty_boat ?boat)
;                     (at_bank ?boat ?y)
                    
;                  )
;     :effect (and (target_in_boat wolf ?boat)
;                  (not (half_empty_boat ?boat))
;                  (full_boat ?boat)
;                  (not (at wolf ?y))
                 
;             )
;   )
  
;   (:action goat_on_boat :parameters (?y - (either southbank northbank) ?boat - boat)
;    :precondition (and
;                     (or
;                         (and
;                             (at wolf southbank)
;                             (at goat southbank)
;                             (at cabbage southbank)
;                             (at_bank ?boat southbank)
;                         )
                        
;                        (and (at wolf northbank)
;                             (at goat northbank)
;                             (at cabbage southbank)
;                             (at_bank ?boat northbank)
;                        )
                       
;                        (and (at wolf northbank)
;                             (at goat southbank)
;                             (at cabbage northbank)
;                             (at_bank ?boat southbank)
;                        )
;                     )
;                     (target_in_boat farmer ?boat)
;                     (half_empty_boat ?boat)
;                     (at goat ?y)
;                     (not (target_in_boat goat ?boat))
;                     (at_bank ?boat ?y)
;                  )
;     :effect (and 
;                  (target_in_boat goat ?boat)
;                  (not (half_empty_boat ?boat))
;                  (full_boat ?boat)
;                  (not (at goat ?y))
                 
;             )
;   )


;   (:action cabbage_on_boat :parameters (?y - (either southbank northbank) ?boat - boat)
;    :precondition (and
;                     (at wolf northbank)
;                     (at goat southbank)
;                     (at cabbage southbank)
;                     (at_bank ?boat southbank)
                    
;                     (target_in_boat farmer ?boat)
;                     (half_empty_boat ?boat)
;                     (at cabbage ?y)
;                     (not (target_in_boat cabbage ?boat))
;                     (at_bank ?boat ?y)
;                  )
;     :effect (and (target_in_boat cabbage ?boat)
;                  (not (half_empty_boat ?boat))
;                  (full_boat ?boat)
;                  (not (at cabbage ?y))
;             )
;   )
  


;   (:action wolf_off_boat :parameters (?y - (either southbank northbank) ?boat - boat)
;    :precondition (and
;                     (at_bank ?boat ?y)
;                     (full_boat ?boat)
;                     (target_in_boat wolf ?boat)
;                     (target_in_boat farmer ?boat)
;                  )
;     :effect (and 
;                  (not (full_boat ?boat))
;                  (half_empty_boat ?boat)
;                  (not (target_in_boat wolf ?boat))
;                  (at wolf ?y)
                 
;             )
;   )

;   (:action goat_off_boat :parameters (?y - (either southbank northbank) ?boat - boat)
;    :precondition (and
;                     (at_bank ?boat ?y)
;                     (full_boat ?boat)
;                     (target_in_boat goat ?boat)
;                     (target_in_boat farmer ?boat)
;                  )
;     :effect (and 
;                  (not (full_boat ?boat))
;                  (half_empty_boat ?boat)
;                  (not (target_in_boat goat ?boat))
;                  (at goat ?y)
                 
;             )
;   )
  
;   (:action cabbage_off_boat :parameters (?y - (either southbank northbank) ?boat - boat)
;    :precondition (and
;                     (at_bank ?boat ?y)
;                     (full_boat ?boat)
;                     (target_in_boat cabbage ?boat)
;                     (target_in_boat farmer ?boat)
;                  )
;     :effect (and 
;                  (not (full_boat ?boat))
;                  (half_empty_boat ?boat)
;                  (not (target_in_boat cabbage ?boat))
;                  (at cabbage ?y)
                 
;             )
;   )  

;   (:action move :parameters (?from ?to - (either left right) ?boat - boat, ?adult - (either father mother officer), ?passenger (either father mother officer boy girl thief))
;    :precondition (and 
;                       (not (empty_boat ?boat))
;                       (at_bank ?boat ?from)
;                       (full_boat ?boat))
;    :effect (and 
;                 (boat_at ?to
;                 (not boat at ?from)
;                 (at ?adult ?to)
;                 (not at ?adult ?from)
;                 (at ?passenger ?to)
;                 (not at ?passenger ?from)
;             )

)