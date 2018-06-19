<Cabbage>
form caption("MIDI Out Simple"), size(400,120), pluginID("Mout")
hslider bounds(14, 80, 381, 40) range(0, 10, 5, 1, 0.001), channel("tempo"), text("Tempo")
</Cabbage>
<CsoundSynthesizer>
<CsOptions>
-dm0 -n -+rtmidi=NULL -M0 -Q0 --midi-key=4 --midi-velocity=5
</CsOptions>
<CsInstruments>
sr 	= 	44100
ksmps 	= 	16
nchnls 	= 	2
0dbfs	=	1

instr	1
    kTempo chnget "tempo"
    kRand randh 100, kTempo
    if changed(kRand) == 1 then
        printks "Note:%d", 0, abs(int(kRand))
        midion2 1, abs(int(kRand)), 1, 1
    endif
endin

</CsInstruments>

<CsScore>
i1 0 z
</CsScore>


</CsoundSynthesizer>