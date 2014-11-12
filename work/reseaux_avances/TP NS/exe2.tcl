# New Simulator
set ns [new Simulator]

#Déclaration des fichiers qui vont contenir les résultats
set ftrace [open trace1.tr w]
set nf [open tp1.nam w]
$ns namtrace-all $nf

# Creation des noeuds
set bleu0 [$ns node]
set bleu1 [$ns node]
set bleu2 [$ns node]
set bleu3 [$ns node]
set jaune [$ns node]
set rouge [$ns node]

# Connection des noeuds entre eux
$ns duplex-link $bleu0 $jaune 10Mb 10ms DropTail
$ns duplex-link $bleu1 $jaune 10Mb 10ms DropTail
$ns duplex-link $bleu2 $jaune 10Mb 10ms DropTail
$ns duplex-link $bleu3 $jaune 10Mb 10ms DropTail
$ns duplex-link $jaune $rouge 1Mb 10ms DropTail
$ns queue-limit $jaune $rouge 10

# Perte de paquets ?
$ns duplex-link-op $jaune $rouge queuePos 0.5

# Creation des 4 agents TCP
set agent0 [new Agent/TCP/RFC793edu]
$agent0 set window_ 5
$agent0 set packetSize_ 1000
set agent1 [new Agent/TCP/RFC793edu]
$agent1 set window_ 5
$agent1 set packetSize_ 1000
set agent2 [new Agent/TCP/RFC793edu]
$agent2 set window_ 5
$agent2 set packetSize_ 1000
set agent3 [new Agent/TCP/RFC793edu]
$agent3 set window_ 5
$agent3 set packetSize_ 1000

# Creation des 4 agents TCP Sink
set agentSink0 [new Agent/TCPSink]
set agentSink1 [new Agent/TCPSink]
set agentSink2 [new Agent/TCPSink]
set agentSink3 [new Agent/TCPSink]

# Attacher les agents TCP aux noeuds
$ns attach-agent $bleu0 $agent0
$ns attach-agent $bleu1 $agent1
$ns attach-agent $bleu2 $agent2
$ns attach-agent $bleu3 $agent3
$ns attach-agent $rouge $agentSink0
$ns attach-agent $rouge $agentSink1
$ns attach-agent $rouge $agentSink2
$ns attach-agent $rouge $agentSink3

# Connections des agents TCP aux agents TCP Sink
$ns connect $agent0 $agentSink0
$ns connect $agent1 $agentSink1
$ns connect $agent2 $agentSink2
$ns connect $agent3 $agentSink3

# Creation des 4 applications FTP pour chacun des 4 agents TCP
set ftp0 [new Application/FTP]
$ftp0 set packetSize_ 1000
$ftp0 set interval_ 0.005
$ftp0 attach-agent $agent0
set ftp1 [new Application/FTP]
$ftp1 set packetSize_ 1000
$ftp1 set interval_ 0.005
$ftp1 attach-agent $agent1
set ftp2 [new Application/FTP]
$ftp2 set packetSize_ 1000
$ftp2 set interval_ 0.005
$ftp2 attach-agent $agent2
set ftp3 [new Application/FTP]
$ftp3 set packetSize_ 1000
$ftp3 set interval_ 0.005
$ftp3 attach-agent $agent3

#Couleurs
$ns color 1 Blue
$agent0 set class_ 1
$ns color 2 Red
$agent1 set class_ 2
$ns color 3 Yellow
$agent2 set class_ 3
$ns color 4 Green
$agent3 set class_ 4

#Procédure qui termine la simulation
proc finish {} {
	global ns nf ftrace
	$ns flush-trace
	close $nf
#	exec nam tp1.nam &
	exit 0
}

# Faire demarrer le bordel
$ns at 0.0 "$ftp0 start"
$ns at 2.0 "$ftp0 stop"
$ns at 0.0 "$ftp1 start"
$ns at 2.0 "$ftp1 stop"
$ns at 0.0 "$ftp2 start"
$ns at 2.0 "$ftp2 stop"
$ns at 0.0 "$ftp3 start"
$ns at 2.0 "$ftp3 stop"
$ns at 2.0 "finish"
$ns run