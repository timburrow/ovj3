
/*ghn_caNLS.c

    3D HNCA gradient sensitivity-enhanced non-linearly sampled version.


    Correlates Ca(i) with N(i), NH(i), and N(i+1), NH(i+1).  Uses constant time
    evolution for the 15N shifts.

    Standard features include maintaining the 13C carrier in the Ca region
    throughout using off-res SLP pulses; square pulses on Ca with first
    null at 13CO; one lobe sinc pulses on 13CO with first null at Ca; one lobe
    sinc pulse to put H2O back along z (the sinc one-lobe is significantly more
    selective than gaussian, square, or seduce 90 pulses); optional 2H 
    decoupling when CaCb magnetization is transverse for 4 channel 
    spectrometers.  

    Magic-angle option for coherence transfer gradients.  TROSY option for
    N15/H1 evolution/detection.
 
    pulse sequence: Ikura, Kay, and Bax, Biochem, 29, 4659 (1990)
                    Grzesiek and Bax, JMR, 96, 432 (1992)
		    Muhandiram and Kay, JMR, B103, 203 (1994)
		    Kay, Xu, and Yamazaki, JMR, A109, 129-133 (1994)            
    SLP pulses:     J Magn. Reson. 96, 94-102 (1992)
    TROSY:	    Weigelt, JACS, 120, 10778 (1998)
    Non-linear sampling:  D.Rovnyak, D.P.Frueh, M.Sastry, Zhen-Yu Sun, A.S.,
                Stern,J.C.Hoch and G.Wagner, JMR, 170, 15 (2004).
 
    Modified from hnco_3c_pfg_laue.c by RM 12/11/92 to add gradient SE.
    Modified by LEK Sept. 19, 1993, Nov 26, 1993, and Dec. 22, 1993 to 
    minimally excite water etc.

    Revised and improved to a standard format by MRB, BKJ and GG for the 
    BioPack, January 1997, so as to include calculation of the above 
    standard features within the pulse sequence code and associated macro.
    TROSY added Dec 98, based on similar addition to gNhsqc.(Version Dec 1998)

    Added optional CO/C-beta decoupling. Cbdec flag controls option. This
    decoupling will possibly interfere with alpha carbons that have 13C shifts
    overlapping the beta regions (e.g. downfield from 63ppm and upfield from
    52 ppm) depending on the waveform used. The waveform should be created
    to decouple both C=O and beta carbons. If Cbdec='y'
    a shaped 13C pulse is used to decouple C=O during t1. (EK jan01)

    Modified the amplitude of the flipback pulse(s) (pwHs)
    to permit user adjustment around theoretical value (tpwrs). 
    If tpwrsf < 4095.0 the value of tpwrs is increased 6db and
    values of tpwrsf of 2048 or so should give equivalent amplitude. 
    In cases of severe radiation damping( which happens during pwHs) 
    the needed flip angle may be much less than 90 degrees, so tpwrsf 
    should be lowered to a value to minimize the observed H2O signal in 
    single-scan experiments (with ssfilter='n').(GG jan01)

    Added non-linear sampling (GG july 2005)

    Made the waltz16 field strength enterable (waltzB1) in Hz.  (GG jan03)
        	  CHOICE OF DECOUPLING AND 2D MODES

    	Set dm = 'nnn', dmm = 'ccc' 
    	Set dm2 = 'nny', dmm2 = 'ccg' (or 'ccw', or 'ccp') for 15N decoupling.
	Set dm3 = 'nnn' for no 2H decoupling, or
		  'nyn'  and dmm3 = 'cwc' for 2H decoupling. 
  

    Must set = 1,2 and phase2 = 1,2 for States-TPPI acquisition in
    t1 [13C]  and t2 [15N].

    The flag f1180/f2180 should be set to 'y' if t1/t2 is to be started at
    halfdwell time. This will give 90, -180 phasing in f1/f2. If it is set to
    'n' the phasing should be 0,0 and will still give a perfect baseline.  Thus,
    set f1180='n' for (0,0) in 13C and f2180='n' for (0,0) in 15N.  f1180='y' is
    ignored if ni=0, and f2180='y' is ignored if ni2=0.



           	  DETAILED INSTRUCTIONS FOR USE OF ghn_caNLS

    1. Obtain a printout of the Philosopy behind the BioPack development,
       and General Instructions using the macro: 
                                      "printon man('BioPack') printoff".
       These Detailed Instructions for ghn_caNLS may be printed using:
                                      "printon man('ghn_caNLS') printoff".
             
    2. Apply the setup macro "ghn_caNLS".  This loads the relevant parameter 
       set and also sets ni=ni2=0 and phase=phase2=1 ready for a 1D spectral 
       check. At the middle of the t1 period, the 180 degree pulses on CO and 
       15N are swapped to a 180 degree pulse on Ca, for the first increment of 
       t1, to refocus Ca chemical-shift evolution ensuring a zero first-order 
       phase correction in F1. This is also the case for the 1D spectral check,
       or for 2D/15N spectra, when ni=0.

    3. Center H1 frequency on H2O (4.7ppm), C13 on 56ppm,  and N15 frequency
       on the amide region (120ppm). The C13 frequency remains at 56ppm,
       ie at Ca throughout the sequence.

    4. The normal 13C 180 degree pulse on CO at the middle of t1 induces a
       phase shift, which should be field-invariant, and so this phase shift 
       has been calibrated and compensated in the pulse sequence. This phase 
       shift can be checked by setting ni=1 whereby a special 
       1D method is invoked in which both the 13C CO 180 degree 
       pulse and the simultaneous 15N 180
       degree pulse are applied just as for all t1 times other than t1=0.  
       First eliminate the CO pulse by setting pwC9=0 and obtain a 1D spectrum.
       This spectrum will have reduced int. compared to ni=0 because of 13Ca
       chemical-shift evolution during the time of the 180 pulses. If the
       phase shift is adequately compensated, a second very similar 1D spectrum
       will be obtained with pwC9=pwC9a.  As described in more detail for  
       ghn_co, a more sensitive comparison of the two spectra with pwC9=0,pwC9a 
       can be obtained with phase=2.  If not adequately compensated, the
       first increment will be out of phase with all succeeding increments and 
       a zero-order phase-shift will be necessary in F1, which is easily done
       after the 2D/3D transform. Alternatively, change the calibration by
       changing the phshift9 parameter in the INITIALIZE VARIABLES section of
       the code. The pulse pwC9 is automatically reset to its calibrated value
       (=pwC9a) within the pulse sequence code for 3D work and 2D/t1 studies.
       DO NOT CHANGE pwC9a from its calibrated value.

    5. H2O preservation is achieved according to Kay et al, except that a sinc
       one-lobe selective pulse is used to put H2O back along z.  This is much
       more selective than a hard, Seduce1, or gaussian pulse.

    6. Another difference from the work of Kay et al is that the phases of both
       Ca 90 degree pulses are alternated to eliminate artifacts from the CO
       180 degree pulse.

    7. timeTN (14 ms) was determined for alphalytic protease and is listed in 
       dg2 for possible readjustment by the user.

    8. The coherence-transfer gradients using power levels
       gzlvl1 and gzlvl2 may be either z or magic-angle gradients. For the
       latter, a proper /vnmr/imaging/gradtable entry must be present and
       syscoil must contain the value of this entry (name of gradtable). The
       amplitude of the gzlvl1 and gzlvl2 should be lower than for a z axis
       probe to have the x and y gradient levels within the 32k range. For
       any value, a dps display (using power display) shows the x,y and z
       dac values. These must be <=32k.

    9. TROSY:
       Set TROSY='y' and dm2='nnn' for a TROSY spectrum of the bottom right
       peak of the 2D coupled NH quartet (high-field H1, low-field N15).  The 
       TROSY spectrum gives 50% S/N compared to the decoupled spectrum for a 
       small peptide.  To select any of the other three peaks of the 2D coupled
       quartet, in a clockwise direction from bottom right, change t4/t10
       from x/y to x/-y to -x/-y to -x/y.  NOTE, the phases of the SE train
       are almost the same as those determined for the gNhsqc sequence.  The
       major difference is that kappa is eliminated compared to normal
       ghn_ca so the N15 magnetization has not evolved with respect to the 
       attached H's.  I.e. the N15 state would be Ix rather than IySz if there 
       was no coherence gradient - this imparts a 90 degree shift so t8 is 
       changed to y (from x in the normal spectrum).  Also gzlvl1 is after the
       180 N15 pulse rather than before as in gNhsqc, so the sign of icosel 
       and the t4/t10 phase2 increments are also swapped compared to gNhsqc.
       For ghn_c... type sequences, H1 decoupling during the first timeTN is
       replaced by a pi pulse at kappa/2 to reduce S/N loss for large molecules
       during the first TN period.  For these sequences H2O flipback is 
       achieved with two sinc one-lobe pulses, an additional one just before
       the SE train, similar to gNhsqc.

   10. Radiation Damping:
       At fields 600MHz and higher with high-Q probes, radiation damping is a
       factor to be considered. Its primary effect is in the flipback pulse
       calibration. Radiation damping causes a rotation back to the +Z axis
       even without a flipback pulse. Hence, the pwHs pulse often needs to 
       be reduced in its flip-angle. This can be accomplished by using the
       parameter tpwrsf. If this value is less than 4095.0 the value of tpwrs
       (calculated in the psg code) is increased by 6dB, thereby permitting
       the value of tpwrsf to be optimized to obtain minimum H2O in the 
       spectrum. The value of tpwrsf is typically lower than 2048 (half-maximum
       to compensate for the extra 6dB in tpwrs). 

   

Non-Linear Sampling (For VNMRJ)
------------------


1) Setup the ghn_ca experiment in the normal manner. In VNMRJ select the 
  "Switch to Non-Linear Sampling" button. This runs the macro "BP_NLSsetup" 
   macro which will create the necessary parameters (sampsched, nli, nli2, 
   t1_counter and t2_counter).
2) Enter the sampling schedule name (this should be placed in your 
   vnmrsys/manual as a simple text file) in the appropriate entry box 
   (sets variable "sampsched")
3) Select "Setup Schedule". This runs the "BP_NLSschedule" macro which uses 
   the sampling schedule to set up t1_counter and t2_counter arrays. The total 
   number of fids and approximate time of the experiment is shown. If a
   different schedule is desired there is a "Clear Schedule" button. 
4) The variables nli and nli2 contain the number of the maximum evol.time inc.
   if the experiment is done with linear sampling. This can be used to
   calculate the resolution in each dimension (nli/sw1 and nli2/sw2) in Hz. 
4) Set phase = 1,2 and phase2 = 1,2 in that order. Leave the ni and ni2 at 1.
   If you type "da" at this point the size of the array should be
   4*(no of points in your sechdule).
5) Choose the appropriate nt, sw1 and sw2.
6) The total evolution time in each dimension is given by the dwell time * max
   point in that dimension. For experiments with constant time evolution in the 
   Nitrogen dimension, make sure that sw is large enough to accommodate 
   the maximum no of Nitrogen dimension points (the limit is that dw*max
   < constant time delay, where max is the largest entry in the 
   sampling scheme for the nitrogen dimension)
7) The non-linear sampled data can be processed and converted into XEASY or
   NMRPipe formats,using the software suite "Rowland NMR Tool Kit" (rnmrtk), 
   available from J. Hoch and A. Stern (http://webmac.rowland.org/rnmrtk/).



*/



#include <standard.h>
  


static int   /*  T is for TROSY='y', phx etc also enable TROSY phase changes */
                      phx[1]={0},   phy[1]={1},

	     phi3[2]  = {0,2},
	     phi5[4]  = {0,0,2,2},
	     phi9[8]  = {0,0,0,0,2,2,2,2},
             rec[4]   = {0,2,2,0},		     recT[4]  = {3,1,1,3};

static double   d2_init=0.0, d3_init=0.0;



pulsesequence()
{



/* DECLARE AND LOAD VARIABLES */

char        f1180[MAXSTR],   		      /* Flag to start t1 @ halfdwell */
            f2180[MAXSTR],    		      /* Flag to start t2 @ halfdwell */
            mag_flg[MAXSTR],      /* magic-angle coherence transfer gradients */
 	    TROSY[MAXSTR],			    /* do TROSY on N15 and H1 */
 	    Cbdec[MAXSTR],                           /* co&cb decoupling flag */
 	    Cbdseq[MAXSTR];                      /* co&cb decoupling sequence */
 
int         icosel,          			  /* used to get n and p type */
            t1_counter=getval("t1_counter"),      /* used for states tppi in t1 */
            t2_counter=getval("t2_counter"),      /* used for states tppi in t2 */
	    nli=getval("nli"),
	    nli2 = getval("nli2");

double      tau1,         				         /*  t1 delay */
            tau2,        				         /*  t2 delay */
            timeTN = getval("timeTN"),     /* constant time for 15N evolution */
	    kappa = 5.4e-3,
	    lambda = 2.4e-3,
            
	pwClvl = getval("pwClvl"), 	        /* coarse power for C13 pulse */
        pwC = getval("pwC"),          /* C13 90 degree pulse length at pwClvl */
	rf0,            	  /* maximum fine power when using pwC pulses */

/* 90 degree pulse at Ca (56ppm), first off-resonance null at CO (174ppm)     */
        pwC1,		              /* 90 degree pulse length on C13 at rf1 */
        rf1,		       /* fine power for 4.7 kHz rf for 600MHz magnet */

/* 180 degree pulse at Ca (56ppm), first off-resonance null at CO(174ppm)     */
        pwC2,		                    /* 180 degree pulse length at rf2 */
        rf2,		      /* fine power for 10.5 kHz rf for 600MHz magnet */

/* the following pulse lengths for SLP pulses are automatically calculated    */
/* by the macro "proteincal".  SLP pulse shapes, "offC9" etc are called       */
/* directly from your shapelib.                    			      */
   pwC9 = getval("pwC9"),  /*180 degree pulse at CO(174ppm) null at Ca(56ppm) */
   pwC9a = getval("pwC9a"),    /* pwC9a=pwC9, but not set to zero when pwC9=0 */
   phshift9,             /* phase shift induced on Ca by pwC9 ("offC9") pulse */
   pwZ,			                   /* the largest of pwC9 and 2.0*pwN */
   pwZ1,                /* the larger of pwC9a and 2.0*pwN for 1D experiments */
   rf9,	                           /* fine power for the pwC9 ("offC9") pulse */

   Cbdpwr = getval("Cbdpwr"),             /* power level for CO&cb decoupling */
   Cbdmf = getval("Cbdmf"),              /* dmf for CO&cb decoupling @ cbdpwr */
   Cbdres = getval("Cbdres"),                /* dres for the CO&Cb decoupling */

   compH = getval("compH"),       /* adjustment for C13 amplifier compression */
   compC = getval("compC"),       /* adjustment for C13 amplifier compression */

   	pwHs = getval("pwHs"),	        /* H1 90 degree pulse length at tpwrs */
   	tpwrs,	  	              /* power for the pwHs ("H2Osinc") pulse */
        tpwrsf = getval("tpwrsf"),    /* fine power for pwHs pulse            */
                                      /* use to adjust for radiation-damping  */

        waltzB1 = getval("waltzB1"),  /* waltz16 field strength (in Hz)     */
   	pwHd,	    		        /* H1 90 degree pulse length at tpwrd */
   	tpwrd,	  	                           /* rf for WALTZ decoupling */

	pwNlvl = getval("pwNlvl"),	              /* power for N15 pulses */
        pwN = getval("pwN"),          /* N15 90 degree pulse length at pwNlvl */

	sw1 = getval("sw1"),
	sw2 = getval("sw2"),

	gt1 = getval("gt1"),  		       /* coherence pathway gradients */
        gzcal = getval("gzcal"),             /* g/cm to DAC conversion factor */
	gzlvl1 = getval("gzlvl1"),
	gzlvl2 = getval("gzlvl2"),

	gt0 = getval("gt0"),				   /* other gradients */
	gt3 = getval("gt3"),
	gt4 = getval("gt4"),
	gt5 = getval("gt5"),
	gstab = getval("gstab"),
	gzlvl0 = getval("gzlvl0"),
	gzlvl3 = getval("gzlvl3"),
	gzlvl4 = getval("gzlvl4"),
	gzlvl5 = getval("gzlvl5"),
	gzlvl6 = getval("gzlvl6");

    getstr("f1180",f1180);
    getstr("f2180",f2180);
    getstr("mag_flg",mag_flg);
    getstr("TROSY",TROSY);
    getstr("Cbdec",Cbdec);
    getstr("Cbdseq",Cbdseq);


/*   LOAD PHASE TABLE    */

	settable(t3,2,phi3);
	settable(t4,1,phx);
	settable(t5,4,phi5);
   if (TROSY[A]=='y')
       {settable(t8,1,phy);
	settable(t9,1,phx);
 	settable(t10,1,phy);
	settable(t11,1,phx);
	settable(t12,4,recT);}
    else
       {settable(t8,1,phx);
	settable(t9,8,phi9);
	settable(t10,1,phx);
	settable(t11,1,phy);
	settable(t12,4,rec);}




/*   INITIALIZE VARIABLES   */

    if( dpwrf < 4095 )
	{ printf("reset dpwrf=4095 and recalibrate C13 90 degree pulse");
	  psg_abort(1); }

    /* maximum fine power for pwC pulses */
	rf0 = 4095.0;
	
     /* 90 degree pulse on Ca, null at CO 118ppm away */
       pwC1 = sqrt(15.0)/(4.0*118.0*dfrq);
        rf1 = 4095.0*(compC*pwC)/pwC1;
        rf1 = (int) (rf1 + 0.5);

    /* 180 degree pulse on Ca, null at CO 118ppm away */
        pwC2 = sqrt(3.0)/(2.0*118.0*dfrq);
        rf2 = (4095.0*compC*pwC*2.0)/pwC2;
        rf2 = (int) (rf2 + 0.5);
        if( rf2 > 4095.0 )
              { printf("Recalibrate so that C13 pw90< 24us*600/sfrq"); psg_abort(1);}

    /* 180 degree one-lobe sinc pulse on CO, null at Ca 118ppm away */
        rf9 = (compC*4095.0*pwC*2.0*1.65)/pwC9a; /* needs 1.65 times more     */
        rf9 = (int) (rf9 + 0.5);                 /* power than a square pulse */

    /* the pwC9 pulse at the middle of t1  */
        if ((nli2 > 0.0) && (nli == 1.0)) nli = 0.0;
        if (pwC9a > 2.0*pwN) pwZ = pwC9a; else pwZ = 2.0*pwN;
        if (Cbdec[A]=='y') 
           pwZ = 2.0*(pwN + 2.0*POWER_DELAY + WFG2_START_DELAY - WFG3_START_DELAY);
        if ((pwC9==0.0) && (pwC9a>2.0*pwN)) pwZ1=pwC9a-2.0*pwN; else pwZ1=0.0;
        if (nli > 1)  pwC9 = pwC9a;
        if ( pwC9 > 0 )  phshift9 = 320.0;
	else             phshift9 = 0.0;

    /* selective H20 one-lobe sinc pulse */
    tpwrs = tpwr - 20.0*log10(pwHs/(compH*pw*1.69)); /* needs 1.69 times more */
    tpwrs = (int) (tpwrs);                       /* power than a square pulse */

    /* power level and pulse time for WALTZ 1H decoupling */
	pwHd = 1/(4.0 * waltzB1) ;                  
	tpwrd = tpwr - 20.0*log10(pwHd/(compH*pw));
	tpwrd = (int) (tpwrd + 0.5);
 


/* CHECK VALIDITY OF PARAMETER RANGES */

    if ( 0.5*nli2*1/(sw2) > timeTN - WFG3_START_DELAY)
       { printf(" nli2 is too big. Make nli2 equal to %d or less.\n", 
  	 ((int)((timeTN - WFG3_START_DELAY)*2.0*sw2))); psg_abort(1);}

    if ( dm[A] == 'y' || dm[B] == 'y' || dm[C] == 'y' )
       { printf("incorrect dec1 decoupler flags! Should be 'nnn' "); psg_abort(1);}

    if ( dm2[A] == 'y' || dm2[B] == 'y' )
       { printf("incorrect dec2 decoupler flags! Should be 'nny' "); psg_abort(1);}

    if ( dm3[A] == 'y' || dm3[C] == 'y' )
       { printf("incorrect dec3 decoupler flags! Should be 'nyn' or 'nnn' ");
							             psg_abort(1);}	
    if ( dpwr2 > 46 )
       { printf("dpwr2 too large! recheck value  "); psg_abort(1);}

    if ( pw > 20.0e-6 )
       { printf(" pw too long ! recheck value "); psg_abort(1);} 
  
    if ( pwN > 100.0e-6 )
       { printf(" pwN too long! recheck value "); psg_abort(1);} 
 
    if ( TROSY[A]=='y' && dm2[C] == 'y')
       { text_error("Choose either TROSY='n' or dm2='n' ! "); psg_abort(1);}



/* PHASES AND INCREMENTED TIMES */

/*  Phase incrementation for hypercomplex 2D data, States-Haberkorn element */

    if (phase1 == 2)   tsadd(t3,1,4);  
    if (TROSY[A]=='y')
	 {  if (phase2 == 2)   				      icosel = +1;
            else 	    {tsadd(t4,2,4);  tsadd(t10,2,4);  icosel = -1;}
	 }
    else {  if (phase2 == 2)  {tsadd(t10,2,4); icosel = +1;}
            else 			       icosel = -1;    
	 }


/*  Set up f1180  */

    if( ix == 1) d2_init = d2;
    tau1 = d2_init + (t1_counter) / sw1;
   
    if((f1180[A] == 'y') && (nli > 1.0)) 
	{ tau1 += ( 1.0 / (2.0*sw1) ); if(tau1 < 0.2e-6) tau1 = 0.0; }
    tau1 = tau1/2.0;


/*  Set up f2180  */

    if( ix == 1) d3_init = d3;
    tau2 = d3_init + (t2_counter) / sw2;

    if((f2180[A] == 'y') && (nli2 > 1.0)) 
	{ tau2 += ( 1.0 / (2.0*sw2) ); if(tau2 < 0.2e-6) tau2 = 0.0; }
    tau2 = tau2/2.0;



/* Calculate modifications to phases for States-TPPI acquisition          */

   if(t1_counter % 2) 
	{ tsadd(t3,2,4); tsadd(t12,2,4); }

   if(t2_counter % 2) 
	{ tsadd(t8,2,4); tsadd(t12,2,4); }



/* BEGIN PULSE SEQUENCE */

status(A);
   	delay(d1);
        if ( dm3[B] == 'y' )
          { lk_hold(); lk_sampling_off();}  /*freezes z0 correction, stops lock pulsing*/

	rcvroff();
	obspower(tpwr);
	decpower(pwClvl);
 	dec2power(pwNlvl);
	decpwrf(rf0);
	obsoffset(tof);
	txphase(zero);
   	delay(1.0e-5);
        if (TROSY[A] == 'n')
	  dec2rgpulse(pwN, zero, 0.0, 0.0);  /* destroy N15 and C13 magnetization */
	decrgpulse(pwC, zero, 0.0, 0.0);
	zgradpulse(gzlvl0, 0.5e-3);
	delay(1.0e-4);
        if (TROSY[A] == 'n')
	  dec2rgpulse(pwN, one, 0.0, 0.0);
	decrgpulse(pwC, zero, 0.0, 0.0);
	zgradpulse(0.7*gzlvl0, 0.5e-3);
	delay(5.0e-4);

   	rgpulse(pw,zero,0.0,0.0);                      /* 1H pulse excitation */

   	dec2phase(zero);
	zgradpulse(gzlvl0, gt0);
	delay(lambda - gt0);

   	sim3pulse(2.0*pw, 0.0, 2.0*pwN, zero, zero, zero, 0.0, 0.0);

   	txphase(one);
	zgradpulse(gzlvl0, gt0);
	delay(lambda - gt0);

 	rgpulse(pw, one, 0.0, 0.0);

    txphase(two);
    if (tpwrsf < 4095.0) 
     {obspwrf(tpwrsf); tpwrs = tpwrs+6;}  /* increases tpwrs by 6dB, now need
                                             tpwrsf to be ~ 2048 for equivalence */
    obspower(tpwrs);	  				

if (TROSY[A]=='y')
   {txphase(two);
    shaped_pulse("H2Osinc", pwHs, two, 5.0e-4, 0.0);
    if (tpwrsf < 4095.0) obspwrf(4095.0);
    obspower(tpwr);
    zgradpulse(gzlvl3, gt3);
    delay(2.0e-4);
    dec2rgpulse(pwN, zero, 0.0, 0.0);

    delay(0.5*kappa - 2.0*pw);

    rgpulse(2.0*pw, two, 0.0, 0.0);

    obspower(tpwrd);	  				       /* POWER_DELAY */
    decphase(zero);
    dec2phase(zero);
    decpwrf(rf2);
    delay(timeTN - 0.5*kappa - POWER_DELAY);
   }
else
   {txphase(zero);
    shaped_pulse("H2Osinc", pwHs, zero, 5.0e-4, 0.0);
    if (tpwrsf < 4095.0) obspwrf(4095.0);
    obspower(tpwrd);
    zgradpulse(gzlvl3, gt3);
    delay(2.0e-4);
    dec2rgpulse(pwN, zero, 0.0, 0.0);

    txphase(one);
    delay(kappa - pwHd - 2.0e-6 - PRG_START_DELAY);

    rgpulse(pwHd,one,0.0,0.0);
    txphase(zero);
    delay(2.0e-6);
    obsprgon("waltz16", pwHd, 90.0);	          /* PRG_START_DELAY */
    xmtron();
    decphase(zero);
    dec2phase(zero);
    decpwrf(rf2);
    delay(timeTN - kappa);
   }

	sim3pulse(0.0, pwC2, 2.0*pwN, zero, zero, zero, 0.0, 0.0);

	decphase(t3);
	decpwrf(rf1);
	delay(timeTN);

	dec2rgpulse(pwN, zero, 0.0, 0.0);
if (TROSY[A]=='n')
   {xmtroff();
    obsprgoff();
    rgpulse(pwHd,three,2.0e-6,0.0);}
	zgradpulse(gzlvl3, gt3);
	txphase(one);
	delay(2.0e-4);
      if ( dm3[B] == 'y' )     /* begins optional 2H decoupling */
        {
          dec3rgpulse(1/dmf3,one,10.0e-6,2.0e-6);
          dec3unblank();
          dec3phase(zero);
          delay(2.0e-6);
          setstatus(DEC3ch, TRUE, 'w', FALSE, dmf3);
        }
        rgpulse(pwHd,one,0.0,0.0);
	txphase(zero);
	delay(2.0e-6);
	obsprgon("waltz16", pwHd, 90.0);	       
	xmtron();
	decrgpulse(pwC1, t3, 0.0, 0.0);
	decphase(zero);

/*   xxxxxxxxxxxxxxxxxxxxxx       13Ca EVOLUTION        xxxxxxxxxxxxxxxxxx    */

if ((nli>1.0) && (tau1>0.0))          /* total 13C evolution equals d2 exactly */
   {         /* 2.0*pwC1/PI compensates for evolution at 64% rate during pwC1 */
	decpwrf(rf9);
     if(tau1 - 2.0*pwC1/PI - WFG3_START_DELAY - 0.5*pwZ > 0.0)
       {	   
         if(Cbdec[A]=='y')
         {         
           hlv(ct,v6); hlv(v6,v6);          /* v6 = 00001111... for Cbdec='y' */
           decpower(Cbdpwr); decpwrf(4095.0); decphase(v6);
           decprgon(Cbdseq,1.0/Cbdmf,Cbdres); decon();  /* COCb decoupling on */
           delay(tau1 - 2.0*pwC1/PI - pwN - WFG2_START_DELAY - POWER_DELAY);
           dec2rgpulse(2.0*pwN,zero,0.0,0.0);
           delay(tau1 - 2.0*pwC1/PI - pwN - POWER_DELAY - WFG2_STOP_DELAY);
           decoff(); decprgoff();                      /* COCb decoupling off */
           decpower(pwClvl); 
         }
         else
         {						/* WFG3_START_DELAY */
	   delay(tau1 - 2.0*pwC1/PI - WFG3_START_DELAY - 0.5*pwZ);
							  
	   sim3shaped_pulse("", "offC9", "", 0.0, pwC9a, 2.0*pwN, zero, zero, zero,
								      0.0, 0.0);
	   initval(phshift9, v9);
	   decstepsize(1.0);
	   dcplrphase(v9);  				        /* SAPS_DELAY */
	   delay(tau1 - 2.0*pwC1/PI  - SAPS_DELAY - 0.5*pwZ - 2.0e-6);
	 }
       }
     else
       {
	 initval(180.0, v9);
	 decstepsize(1.0);
	 dcplrphase(v9);  				        /* SAPS_DELAY */
	 delay(2.0*tau1 - 4.0*pwC1/PI - SAPS_DELAY - 2.0e-6);
       }
   }

else if (nli==1.0)         /* special 1D check of pwC9 phase enabled when nli=1 */
   {
	decpwrf(rf9);
	delay(10.0e-6 + SAPS_DELAY + 0.5*pwZ1);
							  /* WFG3_START_DELAY */
	sim3shaped_pulse("", "offC9", "", 0.0, pwC9, 2.0*pwN, zero, zero, zero,
							          2.0e-6, 0.0);
	initval(phshift9, v9);
	decstepsize(1.0);
	dcplrphase(v9);  					/* SAPS_DELAY */
	delay(10.0e-6 + WFG3_START_DELAY + 0.5*pwZ1);
   }

else			       /* 13Ca evolution refocused for 1st increment  */
   {
	decpwrf(rf2);
	decrgpulse(pwC2, zero, 2.0e-6, 0.0);
   }
        decphase(t5);
	decpwrf(rf1);
	decrgpulse(pwC1, t5, 2.0e-6, 0.0);

/*  xxxxxxxxxxxxxxxxxx    OPTIONS FOR N15 EVOLUTION    xxxxxxxxxxxxxxxxxxxxx  */

	dec2phase(t8);
	xmtroff();
	obsprgoff();
        rgpulse(pwHd,three,2.0e-6,0.0);
	txphase(one);
	dcplrphase(zero);
        if ( dm3[B] == 'y' )   /* turns off 2H decoupling  */
           {
           setstatus(DEC3ch, FALSE, 'c', FALSE, dmf3);
           dec3rgpulse(1/dmf3,three,2.0e-6,2.0e-6);
           dec3blank();
           lk_autotrig();   /* resumes lock pulsing */
           }
	zgradpulse(gzlvl4, gt4);
 	delay(2.0e-4);
        if (TROSY[A]=='n')
	   {rgpulse(pwHd,one,0.0,0.0);
	    txphase(zero);
	    delay(2.0e-6);
	    obsprgon("waltz16", pwHd, 90.0);
	    xmtron();}
	dec2rgpulse(pwN, t8, 0.0, 0.0);

	decphase(zero);
	dec2phase(t9);
	decpwrf(rf2);
	delay(timeTN - tau2);

	sim3pulse(0.0, pwC2, 2.0*pwN, zero, zero, t9, 0.0, 0.0);

	dec2phase(t10);
        decpwrf(rf9);

if (TROSY[A]=='y')
{    if (tau2 > gt1 + 2.0*GRADIENT_DELAY + 1.5e-4 + pwHs)
	{
	  txphase(three);
          delay(timeTN - pwC9a - WFG_START_DELAY);         /* WFG_START_DELAY */
          decshaped_pulse("offC9", pwC9a, zero, 0.0, 0.0);
          delay(tau2 - gt1 - 2.0*GRADIENT_DELAY - 1.5e-4 - pwHs);
          if (mag_flg[A]=='y')  magradpulse(icosel*gzcal*gzlvl1, gt1);
          else  zgradpulse(icosel*gzlvl1, gt1);   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwrs);				       /* POWER_DELAY */
          if (tpwrsf<4095.0)
           { obspwrf(tpwrsf); delay(1.0e-4 - POWER_DELAY -PWRF_DELAY);}
          else
	   delay(1.0e-4 - POWER_DELAY);
   	  shaped_pulse("H2Osinc", pwHs, three, 0.0, 0.0);
	  txphase(t4);
          if (tpwrsf < 4095.0)
           {obspwrf(4095.0); delay(0.5e-4 - POWER_DELAY -PWRF_DELAY);}
          else
	   delay(0.5e-4 - POWER_DELAY);
	  obspower(tpwr);				       /* POWER_DELAY */
	}

    else if (tau2 > pwHs + 0.5e-4)
	{
	  txphase(three);
          delay(timeTN-pwC9a-WFG_START_DELAY-gt1-2.0*GRADIENT_DELAY-1.0e-4);
          if (mag_flg[A]=='y')    magradpulse(icosel*gzcal*gzlvl1, gt1);
          else  zgradpulse(icosel*gzlvl1, gt1);	   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwrs);				       /* POWER_DELAY */
          if (tpwrsf<4095.0) 
           {obspwrf(tpwrsf); delay(1.0e-4 - POWER_DELAY);}
          else
	   delay(1.0e-4 - POWER_DELAY);                     /* WFG_START_DELAY */
          decshaped_pulse("offC9", pwC9a, zero, 0.0, 0.0);
          delay(tau2 - pwHs - 0.5e-4);
   	  shaped_pulse("H2Osinc", pwHs, three, 0.0, 0.0);
	  txphase(t4);
          if (tpwrsf < 4095.0) 
           {obspwrf(4095.0); delay(0.5e-4 - POWER_DELAY - PWRF_DELAY);}
          else
	   delay(0.5e-4 - POWER_DELAY);
	  obspower(tpwr);				       /* POWER_DELAY */
	}
    else
	{
	  txphase(three);
          delay(timeTN - pwC9a - WFG_START_DELAY - gt1 - 2.0*GRADIENT_DELAY
							    - 1.5e-4 - pwHs);
          if (mag_flg[A]=='y')    magradpulse(icosel*gzcal*gzlvl1, gt1);
          else  zgradpulse(icosel*gzlvl1, gt1);	   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwrs);				       /* POWER_DELAY */
          if (tpwrsf<4095.0) 
           {obspwrf(tpwrsf); delay(1.0e-4 - POWER_DELAY - PWRF_DELAY);}
          else
	   delay(1.0e-4 - POWER_DELAY);                     /* WFG_START_DELAY */
   	  shaped_pulse("H2Osinc", pwHs, three, 0.0, 0.0);
	  txphase(t4);
          if (tpwrsf < 4095.0) 
           {obspwrf(4095.0); delay(0.5e-4 - POWER_DELAY - PWRF_DELAY);}
          else
	   delay(0.5e-4 - POWER_DELAY);
	  obspower(tpwr);				       /* POWER_DELAY */
          decshaped_pulse("offC9", pwC9a, zero, 0.0, 0.0);
          delay(tau2);
	}
}
else
{
    if (tau2 > kappa)
	{
          delay(timeTN - pwC9a - WFG_START_DELAY);     	   /* WFG_START_DELAY */
          decshaped_pulse("offC9", pwC9a, zero, 0.0, 0.0);
          delay(tau2 - kappa - PRG_STOP_DELAY - pwHd - 2.0e-6);
          xmtroff();
          obsprgoff();					    /* PRG_STOP_DELAY */
	  rgpulse(pwHd,three,2.0e-6,0.0);
	  txphase(t4);
          delay(kappa - gt1 - 2.0*GRADIENT_DELAY - 1.0e-4);
          if (mag_flg[A]=='y')    magradpulse(icosel*gzcal*gzlvl1, gt1);
          else    zgradpulse(icosel*gzlvl1, gt1);   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwr);				       /* POWER_DELAY */
	  delay(1.0e-4 - POWER_DELAY);
	}
    else if (tau2 > (kappa - pwC9a - WFG_START_DELAY))
	{
          delay(timeTN + tau2 - kappa - PRG_STOP_DELAY - pwHd - 2.0e-6);
          xmtroff();
          obsprgoff();					    /* PRG_STOP_DELAY */
	  rgpulse(pwHd,three,2.0e-6,0.0);
	  txphase(t4);                                     /* WFG_START_DELAY */
          decshaped_pulse("offC9", pwC9a, zero, 0.0, 0.0);
          delay(kappa -pwC9a -WFG_START_DELAY -gt1 -2.0*GRADIENT_DELAY -1.0e-4);
          if (mag_flg[A]=='y')    magradpulse(icosel*gzcal*gzlvl1, gt1);
          else    zgradpulse(icosel*gzlvl1, gt1);   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwr);				       /* POWER_DELAY */
	  delay(1.0e-4 - POWER_DELAY);
	}
    else if (tau2 > gt1 + 2.0*GRADIENT_DELAY + 1.0e-4)
	{
          delay(timeTN + tau2 - kappa - PRG_STOP_DELAY - pwHd - 2.0e-6);
          xmtroff();
          obsprgoff();					    /* PRG_STOP_DELAY */
	  rgpulse(pwHd,three,2.0e-6,0.0);
	  txphase(t4);
          delay(kappa - tau2 - pwC9a - WFG_START_DELAY);   /* WFG_START_DELAY */
          decshaped_pulse("offC9", pwC9a, zero, 0.0, 0.0);
          delay(tau2 - gt1 - 2.0*GRADIENT_DELAY - 1.0e-4);
          if (mag_flg[A]=='y')    magradpulse(icosel*gzcal*gzlvl1, gt1);
          else    zgradpulse(icosel*gzlvl1, gt1);   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwr);				       /* POWER_DELAY */
	  delay(1.0e-4 - POWER_DELAY);
	}
    else
	{
          delay(timeTN + tau2 - kappa - PRG_STOP_DELAY - pwHd - 2.0e-6);
          xmtroff();
	  obsprgoff();					    /* PRG_STOP_DELAY */
	  rgpulse(pwHd,three,2.0e-6,0.0);
	  txphase(t4);
    	  delay(kappa-tau2-pwC9a-WFG_START_DELAY-gt1-2.0*GRADIENT_DELAY-1.0e-4);
          if (mag_flg[A]=='y')    magradpulse(icosel*gzcal*gzlvl1, gt1);
          else    zgradpulse(icosel*gzlvl1, gt1);   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwr);				       /* POWER_DELAY */
	  delay(1.0e-4 - POWER_DELAY);                    /* WFG_START_DELAY */
          decshaped_pulse("offC9", pwC9a, zero, 0.0, 0.0);
          delay(tau2);
	}
}                                                          
/*  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  */
	if (TROSY[A]=='y')  rgpulse(pw, t4, 0.0, 0.0);
	else                sim3pulse(pw, 0.0, pwN, t4, zero, t10, 0.0, 0.0);

	txphase(zero);
	dec2phase(zero);
	zgradpulse(gzlvl5, gt5);
	if (TROSY[A]=='y')   delay(lambda - 0.65*(pw + pwN) - gt5);
	else   delay(lambda - 1.3*pwN - gt5);

	sim3pulse(2.0*pw, 0.0, 2.0*pwN, zero, zero, zero, 0.0, 0.0);

	zgradpulse(gzlvl5, gt5);
	txphase(one);
	dec2phase(t11);
	delay(lambda - 1.3*pwN - gt5);

	sim3pulse(pw, 0.0, pwN, one, zero, t11, 0.0, 0.0);

	txphase(zero);
	dec2phase(zero);
	zgradpulse(gzlvl6, gt5);
	delay(lambda - 1.3*pwN - gt5);

	sim3pulse(2.0*pw, 0.0, 2.0*pwN, zero, zero, zero, 0.0, 0.0);

	dec2phase(t10);
	zgradpulse(gzlvl6, gt5);
	if (TROSY[A]=='y')   delay(lambda - 1.6*pwN - gt5);
	else   delay(lambda - 0.65*pwN - gt5);

	if (TROSY[A]=='y')   dec2rgpulse(pwN, t10, 0.0, 0.0); 
	else    	     rgpulse(pw, zero, 0.0, 0.0); 

	delay((gt1/10.0) + 1.0e-4 +gstab - 0.5*pw + 2.0*GRADIENT_DELAY + POWER_DELAY);

	rgpulse(2.0*pw, zero, 0.0, rof1);
	dec2power(dpwr2);				       /* POWER_DELAY */
        if (mag_flg[A] == 'y')    magradpulse(gzcal*gzlvl2, gt1/10.0);
        else   zgradpulse(gzlvl2, gt1/10.0);            /* 2.0*GRADIENT_DELAY */

        delay(gstab);
        rcvron();
statusdelay(C,1.0e-4  - rof1);
   if (dm3[B]=='y') lk_sample();

	setreceiver(t12);
}		 
