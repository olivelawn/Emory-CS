Object subclass: #ParkMillerRNG
    instanceVariableNames: 'seed'
    classVariableNames: 'PMa PMm PMmu1 PMq PMr'
    poolDictionaries: '' 
    category: nil !

ParkMillerRNG comment: 'I implement Park/Miller random number generation' !

!ParkMillerRNG class methodsFor: 'initialization'!
initialize
    PMa := 16r00041A7.
    PMm := 16r7FFFFFF.
    PMq := 16r001F31D.
    PMr := 16r0000B14.
    PMmu1 := 0.46566128752457969e-9.
!!

!ParkMillerRNG class methodsFor: 'creating RNG instances'!
new
    self initialize.
    ^ super new initialize 
!!

!ParkMillerRNG methodsFor: 'initializing starting seed'!
initialize
    " Set a reasonable Park-Miller random starting seed "
    seed := 45678901
!!

!ParkMillerRNG methodsFor: 'next random float between 0.0 and 1.0'!
next
    seed := self peekInteger.
    ^ seed * PMmu1
!!

!ParkMillerRNG methodsFor: 'next random integer between 0 and 16r7FFFFFFF'!
nextInteger
    seed := self peekInteger.
    ^ seed
!!

!ParkMillerRNG methodsFor: 'peek at next float'!
peek
    ^ self peekInteger * PMmu1
!!

!ParkMillerRNG methodsFor: 'peek at next integer'!
peekInteger
    | lo hi aLoRHi answer |
    hi := seed quo: PMq.
    lo := seed rem: PMq.
    aLoRHi := (PMa * lo) - (PMr * hi).
    answer := (aLoRHi > 0)
	ifTrue: [ ^ aLoRHi ].
    ^ aLoRHi + PMm
!!

!ParkMillerRNG methodsFor: 'seed the RNG'!
seed: anInteger
     seed := anInteger
!!


"***************************************************************"


Object subclass: #Myarray
     instanceVariableNames: 'sarray rng'
     classVariableNames: ''
     poolDictionaries: ''
     category: nil !

Myarray comment: 'This is an array to be filled with rand numbers' !

!Myarray class methodsFor: 'instance creation'!
new

     | r |

     r:= super new.
     r init.
     ^ r.

!!


!Myarray methodsFor: 'instance initialization'!
init

     sarray:=Array new: 20.
     rng:=ParkMillerRNG new.
     
     1 to: 20 do: [:ii| sarray at: ii put: ((rng nextInteger)rem: 100)].

!!


!Myarray methodsFor: 'printing'!
printOn: aStream
     super printOn: aStream.
     'sarray has contents' printOn: aStream.
     sarray printOn: aStream.
!!




"******************************************************************"



Myarray subclass: #Maxsum
     instanceVariableNames: 'max'
     classVariableNames: ''
     poolDictionaries: ''
     category: nil !  

Maxsum comment: 'This object computes the Maxsum of a sequence' !

!Maxsum class methodsFor: 'instance creation'!
new

     | s |

     s:= super new.
     s init.
     ^ s.

!!


!Maxsum methodsFor: 'instance initialization'!
init
     
     max:= 0.
     ^ super init.

!!


!Maxsum methodsFor: 'compute the Maxsum'!  
compute

     | ii jj this |
                       
     ii:=0. jj:=0. max:=0.
     this:=0.

     1 to: 20 do: [:jj|
         this:= (this + (sarray at: jj)).

         (this > max)
             ifTrue: [ max:= this ]
             ifFalse: [ (this < 0)
                           ifTrue: [ ii:= jj + 1. this:=0 ].
                      ].
                  ].

      ^ max.
!!




!Maxsum methodsFor: 'printing'!
printOn: aStream
     super printOn: aStream.
     'Maxsum is ' printOn: aStream.
     max printOn: aStream.
"     'sarray[1]= ' printOn: aStream."
"     (sarray at: 1) printOn: aStream."
!!



