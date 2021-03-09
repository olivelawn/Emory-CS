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

