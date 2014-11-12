# New Simulator
set ns [new Simulator]
$ns rtproto DV

#Déclaration des fichiers qui vont contenir les résultats
set ftrace [open trace1_exe3.tr w]
set nf [open tp1_exe3.nam w]
$ns namtrace-all $nf

# Creation des noeuds
set jaune [$ns node]
set bleu0 [$ns node]
set bleu1 [$ns node]
set vert0 [$ns node]
set vert1 [$ns node]
set vert2 [$ns node]

# Connection des noeuds entre eux
$ns duplex-link $jaune $bleu0 10Mb 20ms DropTail
$ns duplex-link $jaune $bleu1 10Mb 20ms DropTail
$ns duplex-link $bleu0 $bleu1 10Mb 20ms DropTail
$ns duplex-link $bleu0 $vert0 10Mb 20ms DropTail
$ns duplex-link $bleu1 $vert0 10Mb 20ms DropTail
$ns duplex-link $bleu1 $vert1 10Mb 20ms DropTail
$ns duplex-link $vert0 $vert1 10Mb 20ms DropTail
$ns duplex-link $vert0 $vert2 10Mb 20ms DropTail
$ns duplex-link $vert1 $vert2 10Mb 20ms DropTail

# Creation des 3 agents UDP
set agent0 [new Agent/UDP]
set null0 [new Agent/Null]
set agent1 [new Agent/UDP]
set null1 [new Agent/Null]
set agent2 [new Agent/UDP]
set null2 [new Agent/Null]

# Attacher les agents TCP aux noeuds
$ns attach-agent $jaune $agent0
$ns attach-agent $vert0 $null0
$ns attach-agent $jaune $agent1
$ns attach-agent $vert1 $null1
$ns attach-agent $jaune $agent2
$ns attach-agent $vert2 $null2
$ns connect $agent0 $null0
$ns connect $agent1 $null1
$ns connect $agent2 $null2

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 5000
$cbr0 set interval_ 0.013
set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 5000
$cbr1 set interval_ 0.013
set cbr2 [new Application/Traffic/CBR]
$cbr2 set packetSize_ 5000
$cbr2 set interval_ 0.013

$cbr0 attach-agent $agent0
$cbr1 attach-agent $agent1
$cbr2 attach-agent $agent2

# Modifier les couts des liens
#$ns cost $bleu0 $bleu1 0.1
#$ns cost $bleu1 $vert0 0.1
#$ns cost $vert0 $vert1 0.1

# Panne à 0.3 seconde
#$ns rtmodel-at 0.3 down $bleu1 $vert0

#Couleurs
$ns color 1 Blue
$agent0 set class_ 1
$ns color 2 Red
$agent1 set class_ 2
$ns color 3 Yellow
$agent2 set class_ 3

#Procédure qui termine la simulation
proc finish {} {
	global ns nf ftrace
	$ns flush-trace
	close $nf
#	exec nam tp1.nam &
	exit 0
}

# Faire demarrer le bordel
$ns at 0.0 "$cbr0 start"
$ns at 1.0 "$cbr0 stop"
$ns at 0.0 "$cbr1 start"
$ns at 1.0 "$cbr1 stop"
$ns at 0.0 "$cbr2 start"
$ns at 1.0 "$cbr2 stop"
$ns at 1.0 "finish"
$ns run