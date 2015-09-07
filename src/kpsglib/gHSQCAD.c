// Copyright (C) 2015  Stanford University
// You may distribute under the terms of either the GNU General Public
// License or the Apache License, as specified in the README file.
// For more information, see the README file.
/* gHSQCAD - Gradient Selected phase-sensitive HSQC
		Adiabatic version

        Features included:
                F1 Axial Displacement

        Paramters:
                sspul :         selects magnetization randomization option
                nullflg:        selects TANGO-Gradient option
                hsglvl:         Homospoil gradient level (DAC units)
                hsgt    :       Homospoil gradient time
                gzlvlE  :       encoding Gradient level
                gtE     :       encoding gradient time
                EDratio :       Encode/Decode ratio
                gstab   :       recovery delay
                j1xh    :       One-bond XH coupling constant

KrishK  -       Last revision   : June 1997
KrishK  -       Revised         : July 2004

*/

#include <standard.h>
#include <chempack.h>

static int ph1[4]  = {1,1,3,3},
           ph2[2]  = {0,2,},
           ph3[8]  = {0,0,0,0,2,2,2,2},
           ph4[16] = {0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
           ph5[16] = {1,3,3,1,3,1,1,3,3,1,1,3,1,3,3,1};

pulsesequence()

{

   double   gzlvlE = getval("gzlvlE"),
            gtE = getval("gtE"),
            EDratio = getval("EDratio"),
            gstab = getval("gstab"),
            mult = getval("mult"),
	    pwx180 = getval("pwx180"),
	    pwxlvl180 = getval("pwxlvl180"),
	    pwx180r = getval("pwx180r"),
	    pwxlvl180r = getval("pwxlvl180r"),
            hsglvl = getval("hsglvl"),
            hsgt = getval("hsgt"),
            tau,
            taug;
   int      icosel,
	    phase1 = (int)(getval("phase")+0.5),
	    ZZgsign;
   char	    pwx180ad[MAXSTR],
	    pwx180adR[MAXSTR],
	    pwx180ref[MAXSTR];

//synchronize gradients to srate for probetype='nano'
//   Preserve gradient "area"
        gtE = syncGradTime("gtE","gzlvlE",0.5);
        gzlvlE = syncGradLvl("gtE","gzlvlE",0.5);

  getstr("pwx180ad", pwx180ad);
  getstr("pwx180adR", pwx180adR);
  getstr("pwx180ref", pwx180ref);
  tau = 1 / (4*(getval("j1xh")));

  if (mult > 0.5)
    taug = 2*tau + getval("tauC");
  else
    taug = gtE + gstab + 2 * GRADIENT_DELAY;
  ZZgsign=-1; 
  if (mult == 2) ZZgsign=1;
  icosel = 1;
  
  settable(t1, 4, ph1);
  settable(t2, 2, ph2);
  settable(t3, 8, ph3);
  settable(t4, 16, ph4);
  settable(t5, 16, ph5);

  getelem(t2, ct, v2);
  getelem(t5, ct, oph);

  if ((phase1 == 2) || (phase1 == 5))
    icosel = -1;
/*
  mod2(id2, v14);
  dbl(v14,v14);
*/
  initval(2.0*(double)(((int)(d2*getval("sw1")+0.5)%2)),v14);

  add(v2, v14, v2);
  add(oph, v14, oph);

status(A);
   obspower(tpwr);

   delay(5.0e-5);
   if (getflag("sspul"))
        steadystate();

   if (satmode[0] == 'y')
     {
        if ((d1-satdly) > 0.02)
                delay(d1-satdly);
        else
                delay(0.02);
        satpulse(satdly,zero,rof1,rof1);
     }
   else
        delay(d1);

   if (getflag("wet"))
     wet4(zero,one);

   decpower(pwxlvl);

  status(B);

    if (getflag("nullflg"))
    {
      rgpulse(0.5 * pw, zero, rof1, rof1);
      delay(2 * tau);
      decpower(pwxlvl180);
      decshaped_pulse(pwx180ad, pwx180, zero, rof1, rof1);
      rgpulse(2.0 * pw, zero, rof1, rof1);
      delay(2 * tau + 2 * POWER_DELAY);
      decshaped_pulse(pwx180adR, pwx180, zero, rof1, rof1);
      decpower(pwxlvl);
      rgpulse(1.5 * pw, two, rof1, rof1);
      zgradpulse(hsglvl, hsgt);
      delay(1e-3);
    }

    rgpulse(pw, zero, rof1, rof1);
    delay(tau);
    decpower(pwxlvl180);
    decshaped_pulse(pwx180ad, pwx180, zero, rof1, rof1);
    rgpulse(2.0 * pw, zero, rof1, rof1);
    delay(tau + 2 * POWER_DELAY);
    decshaped_pulse(pwx180adR, pwx180, zero, rof1, rof1);
    decpower(pwxlvl);
    rgpulse(pw, t1, rof1, rof1);
    zgradpulse(hsglvl, 2 * hsgt);
    delay(1e-3);
    decrgpulse(pwx, v2, rof1, 2.0e-6);

    if (d2 / 2 > 0.0)
      delay(d2 / 2 - (2 * pwx / PI) - pw - 4.0e-6);
    else
      delay(d2 / 2);
    rgpulse(2 * pw, zero, 2.0e-6, 2.0e-6);
    if (d2 / 2 > 0.0)
      delay(d2 / 2 - (2 * pwx / PI) - pw - 4.0e-6);
    else
      delay(d2 / 2);

    delay(taug - POWER_DELAY);
    decpower(pwxlvl180r);
    decshaped_pulse(pwx180ref, pwx180r, zero, rof1, rof1);
    rgpulse(mult * pw, zero, rof1, rof1);
    delay(taug - mult * pw - 2 * rof1 + POWER_DELAY - gtE - gstab - 2 * GRADIENT_DELAY);
    zgradpulse(gzlvlE, gtE);
    delay(gstab);
    decshaped_pulse(pwx180ref, pwx180r, zero, rof1, rof1);
    decpower(pwxlvl);

    decrgpulse(pwx, t4, 2.0e-6, rof1);
    zgradpulse(ZZgsign*0.6 * hsglvl, 1.2 * hsgt);
    delay(1e-3);
    rgpulse(pw, t3, rof1, rof1);
    decpower(pwxlvl180);
    decshaped_pulse(pwx180adR, pwx180, zero, rof1, rof1);
    decpower(dpwr);
    delay(tau - (2 * pw / PI) - 2 * rof1);
    rgpulse(2 * pw, zero, rof1, rof2);
    decpower(pwxlvl180);
    decshaped_pulse(pwx180ad, pwx180, zero, rof1, rof1);
    decpower(dpwr);
    zgradpulse(icosel * 2.0*gzlvlE/EDratio, gtE/2.0);
    delay(tau - gtE/2.0 - 2 * GRADIENT_DELAY);
  status(C);
}