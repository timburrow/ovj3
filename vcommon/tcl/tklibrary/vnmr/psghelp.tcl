# @(#)psghelp.tcl 10.1 01/13/06 Copyright (c) 1991-1994 Varian Assoc.,Inc. All Rights Reserved
# 
# Copyright (c) 1991-1994 Varian Assoc.,Inc. All Rights Reserved. 
# This software contains proprietary and confidential
# information of Varian Assoc., Inc. and its contributors.
# Use, disclosure and reproduction is prohibited without
# prior consent.
#
proc helpMouse {helpFile} {
   global pInfo
   catch {destroy .help}
   toplevel .help
   if {[info exists pInfo(helpGeom)] == 1} {
      wm geometry .help $pInfo(helpGeom)
   }
   set theHelp "No help!\n"
   set theFile [file join $pInfo(homeDir) help $helpFile]
   if {[file exists $theFile] == 1} {
    set file [open $theFile r]
    set theHelp [read $file]
    close $file
   }
   frame .help.mouseHelp
   text .help.mouseHelp.t -wrap word -setgrid true -relief flat  \
        -highlightthickness 0 -yscrollcommand ".help.mouseHelp.s set"
   scrollbar .help.mouseHelp.s -command ".help.mouseHelp.t yview"
   pack .help.mouseHelp.s -side right -fill y
   pack .help.mouseHelp.t -side left
   .help.mouseHelp.t insert end $theHelp
   pack .help.mouseHelp -side top -fill both
   wm protocol .help  WM_DELETE_WINDOW {
      set pInfo(helpGeom) [wm geometry .help]
      destroy .help
   }
}