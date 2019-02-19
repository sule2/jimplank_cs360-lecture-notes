
proc animate { } {
  global g
  if { $g("animok") == 1 } {
    step
    after $g("animdelay") animate
    .mv.buttons.anim.animate configure -text "Stop Animation" -command un_animate
  } else {
    set g("animok") 1
    .mv.buttons.anim.animate configure -text Animate -command animate
  }
}

proc animtoggle { } {
  global g
  if { $g("animdelay") == 1000 } {
    set g("animdelay") 100
    .mv.buttons.anim.animtoggle configure -text "Make Animation Slow" 
  } else {
    set g("animdelay") 1000
    .mv.buttons.anim.animtoggle configure -text "Make Animation Fast" 
  }
}

proc scroll_code_down { } {
  global g
  set fcd [ expr $g("firstcodedraw") + $g("nrows") * 2 ]
  if { $fcd % 4 != 0 } { incr fcd -2 }
  set gkey "addval $fcd"
  if { [ catch { set g($gkey) } ] } {
    return
  } else {
    set g("firstcodedraw") $fcd
  }
  redraw
  return
}

proc scroll_code_up { } {
  global g
  set g("firstcodedraw") [ expr $g("firstcodedraw") - $g("nrows") * 2 ]
  if { $g("firstcodedraw") % 4 != 0 } { 
    set g("firstcodedraw") [ expr $g("firstcodedraw") + 2 ]
  }
  if { $g("firstcodedraw") < $g("saddr") } {
    set g("firstcodedraw") $g("saddr")
  }
  redraw
  return
}

proc scroll_stack_up { } {
  global g
  set fcd [ expr $g("stackbase") - $g("nrows") * 2 ]
  if { $fcd % 4 != 0 } { incr fcd 2 }
  set gkey "addval $fcd"
  if { [ catch { set g($gkey) } ] } {
    return
  } else {
    set g("stackbase") $fcd
  }
  redraw
  return
}

proc scroll_stack_down { } {
  global g
  set g("stackbase") [ expr $g("stackbase") + $g("nrows") * 2 ]
  if { $g("stackbase") % 4 != 0 } { 
    set g("stackbase") [ expr $g("stackbase") - 2 ]
  }
  if { $g("stackbase") > $g("stackabsbottom") } {
    set g("stackbase") $g("stackabsbottom")
  }
  redraw
  return
}

proc un_animate { } {
  global g
  set g("animok") 0
  return
}

proc redraw { } {

  global g

  set g("nrows") [ .mv.buttons.height.scale get ]
  set g("height") [ expr $g("rowheight")*$g("nrows") + 2*$g("rowheight") ]
  .mv.c configure -height $g("height")
  
  clear

  if { $g("filename") == "/" } {
      .mv.c create text [ expr $g("width")/2 ] [ expr $g("height")/2 ] \
            -text "No Program Yet" \
            -anchor w \
            -fill white -font { Helvetica 16 bold } -tag upload
  } else {
    draw_registers
    draw_code
    draw_globals
    draw_csr
    draw_stack
  }
}
  
proc draw_registers {} {
  global g

  set x $g("regleft")
  set y [ expr $g("regtop") + $g("rowheight") * 3 ]
  set ny [ expr $y - $g("rowheight") ]

   .mv.c create text [ expr $x+$g("regwidth")/2  ] [ expr ($y+$ny)/2 ] \
        -text Registers -fill white \
            -font { Courier 11 normal } 

  for { set i 0 } { $i < 8 } { incr i } {

    set color Cyan
    if { $i == 5 } { 
      set reg "sp" 
    } elseif { $i == 6 } { 
      set reg "fp" 
    } elseif { $i == 7 } { 
      set reg "pc"
      set color yellow
    } else {
      set reg [ format "r%d" $i ]
    }

    set ny [ expr $y + $g("rowheight") ]
    .mv.c create rectangle $x $y \
       [ expr $x + $g("regwidth") ] $ny -fill black -outline white

    .mv.c create text [ expr $x - 5 ] [ expr ($y+$ny)/2 ] -text $reg \
      -fill white -anchor e -font { Courier 11 normal} 
       
    if { $g($reg) != "" } {
      .mv.c create text [ expr $x+$g("regwidth")/2 ] [ expr ($y+$ny)/2 ] \
        -text [ format "0x%x" [ expr $g($reg) & 0xffffffff ] ] \
        -fill $color -justify center -font { Courier 11 normal} 
    }
       
    if { $reg == "fp" || $reg == "sp" } {
      set stoff [ expr ($g($reg) - $g("stackbase")) / 4 + $g("nrows") - 1 ]
      if { $stoff >= 0 && $stoff < $g("nrows") } {
        set x1 $g("regleft") 
        set x3 [ expr $g("stackleft") + $g("stackwidth") ]
        set x2a [ expr $x1 + ($x3-$x1)/4 ]
        set x2b [ expr $x1 + 7 * ($x3-$x1)/8 ]
        set y1 [ expr ($y+$ny)/2 ] 
        set y2 \
        [ expr $g("stacktop") + $g("rowheight") * $stoff+$g("rowheight")/2 ] 
        .mv.c create line $x1 $y1 $x2a $y1 $x2b $y2 $x3 $y2 \
                      -fill cyan -tag arrows -arrow last \
                      -arrowshape [ list 10 10 5 ]
      }
    }

    if { $reg == "pc" } {
      set codeoff [ expr ($g($reg) - $g("firstcodedraw")) / 4 ]
      if { $codeoff >= 0 && $codeoff < $g("nrows") } {
        set x1 [ expr $x+$g("regwidth") ]
        set x3 $g("codeleft")
        set x2a [ expr $x1 + ($x3-$x1)/4 ]
        set x2b [ expr $x1 + 7 * ($x3-$x1)/8 ]
        set y1 [ expr ($y+$ny)/2 ] 
        set y2 \
        [ expr $g("codetop") + $g("rowheight") * $codeoff+$g("rowheight")/2 ] 
        .mv.c create line $x1 $y1 $x2a $y1 $x2b $y2 $x3 $y2 \
                      -fill yellow -tag arrows -arrow last \
                      -arrowshape [ list 10 10 5 ]
       }
    }

    set y $ny
  }
}

proc draw_csr {} {
  global g

  set x $g("regleft")
  set y [ expr $g("regtop") + $g("rowheight") * 0 ]
  set ny [ expr $y - $g("rowheight") ]

  set sno $g("stepno")
  set lcm $g("lastcmp")
  set val $g("csrval")

  .mv.c create text [ expr $x+$g("regwidth")/2  ] [ expr ($y+$ny)/2 ] \
        -text "Step $sno" -fill white \
        -font { Courier 11 normal } 
  
  set ny [ expr $y + $g("rowheight") ]
  .mv.c create rectangle $x $y \
       [ expr $x + $g("regwidth") ] $ny -fill black -outline white

  .mv.c create text [ expr $x - 5 ] [ expr ($y+$ny)/2 ] -text CSR \
      -fill white -anchor e -font { Courier 11 normal} 
       
  if { $g("stepno") == $g("lastcmp") } {
    .mv.c create text [ expr $x+$g("regwidth")/2 ] [ expr ($y+$ny)/2 ] \
        -text $g("csrval") -fill white \
        -font { Courier 11 normal } 
  }
       
}
proc draw_globals {} {
  global g

  set x $g("regleft")
  set y [ expr $g("regtop") + $g("rowheight") * 13 ]
  set ny [ expr $y - $g("rowheight") ]

   .mv.c create text [ expr $x+$g("regwidth")/2  ] [ expr ($y+$ny)/2 ] \
        -text Globals -fill white \
            -font { Courier 11 normal } 
  
  for { set i 0 } { $i < $g("nglobalrows") } { incr i } {
    set gindex [ expr $i + $g("firstglobal") ]
    if { $gindex >= $g("nglobals") } return

    set ny [ expr $y + $g("rowheight") ]
    .mv.c create rectangle $x $y \
       [ expr $x + $g("regwidth") ] $ny -fill black -outline white

    set gkey "globaladd $gindex"
    set address $g($gkey)
    set gkey "addval $address"
    set value $g($gkey)
    set gkey "globalnum $gindex"
    set name $g($gkey)

    .mv.c create text [ expr $x - 5 ] [ expr ($y+$ny)/2 ] \
      -text [ format "0x%x" [ expr $address & 0xffffffff ] ] \
      -fill white -anchor e -font { Courier 11 normal} 
       
    .mv.c create text [ expr $x+$g("regwidth")/2 ] [ expr ($y+$ny)/2 ] \
        -text [ format "0x%x" [ expr $value & 0xffffffff ] ] \
        -fill Cyan -justify center -font { Courier 11 normal} 
    .mv.c create text [ expr $x + $g("regwidth") + 10 ] [ expr ($y+$ny)/2 ] \
      -text $name -fill LightPink -anchor w \
      -font { Courier 11 normal } 
    set y $ny
  }
       
}

proc draw_stack {} {
  global g

  set x $g("stackleft")
  set y [ expr $g("stacktop") ]
  set ny [ expr $y - $g("rowheight") ]

   .mv.c create text [ expr $x+$g("stackwidth")/2  ] [ expr ($y+$ny)/2 ] \
        -text Stack -fill white \
            -font { Courier 11 normal } 

  set y [ expr $g("stacktop") + $g("rowheight") * ($g("nrows") -1 )]

  set address $g("stackbase")

  for { set i 0 } { $i < $g("nrows") } { incr i } {
    if { $address <= $g("stacktos") } return
    set gkey "addval $address"
    set value $g($gkey)
    
    set ny [ expr $y + $g("rowheight") ]
    .mv.c create rectangle $x $y \
       [ expr $x + $g("stackwidth") ] $ny -fill black -outline white

    .mv.c create text [ expr $x - 5 ] [ expr ($y+$ny)/2 ] \
      -text [ format "0x%x" [ expr $address & 0xffffffff ] ]\
      -fill white -anchor e -font { Courier 11 normal} 
       
    .mv.c create text [ expr $x+$g("stackwidth")/2 ] [ expr ($y+$ny)/2 ] \
        -text [ format "0x%x" [ expr $value & 0xffffffff ] ] \
        -fill Cyan -justify center -font { Courier 11 normal} 
    set y [ expr $y - $g("rowheight") ]
    incr address -4
  }
       
}

proc draw_code {} {
  global g


  set x $g("codeleft")
  set y $g("codetop")
  set ny [ expr $y - $g("rowheight") ]
  
   .mv.c create text [ expr $x+$g("codewidth")/2  ] [ expr ($y+$ny)/2 ] \
        -text Code -fill white \
            -font { Courier 11 normal } 

  set fa [ expr $g("firstcodedraw") + 0 ]
  set top [ expr ( $g("iaddr") - $fa )  ]
  if { $top > [ expr $g("nrows") * 4 ] } { 
    set top [ expr $g("nrows") * 4 ] 
  }

  for { set i 0 } { $i < $top } { incr i 4 } {
    set ny [ expr $y + $g("rowheight") ]
    .mv.c create rectangle $x $y \
       [ expr $x + $g("codewidth") ] $ny -fill black -outline white
    set j [ expr $i + $fa ]
    set key "addval $j"
    set color white
    set reg "pc"
    if { [ expr $i + $fa ] == [ expr $g($reg) + 0 ] } { set color yellow }
    .mv.c create text [ expr $x + 10 ] [ expr ($y+$ny)/2 ] \
      -text $g($key) -fill $color -anchor w \
      -font { Courier 10 normal } 
    .mv.c create text [ expr $x - 10 ] [ expr ($y+$ny)/2 ] \
      -text [ format "0x%x" [ expr [ expr $i + $fa ] & 0xffffffff ] ] -fill white \
      -font { Courier 11 normal } -anchor e
    set add [ expr $i + $fa + 0]
    set addkey "addkey $add"
    .mv.c create text [ expr $x + $g("codewidth") + 10 ] [ expr ($y+$ny)/2 ] \
      -text $g($addkey) -fill LightPink -anchor w \
      -font { Courier 11 normal } 
    
    set y $ny
  }

}

proc clear { } {
  global g
  
  .mv.c create rectangle 0 0 $g("width") $g("height") -fill DarkSlateGray
}


proc read_file { f } {
  global g

  if { [ catch { set gf [ open $f r ] } ] } {
    tk_dialog .mv.error "Open file error" "Can't open file $f" \
              {}  0  "OK"
    return
  }

  set g("file") $f
  set g("filename") $f

  set lineno 0

  while {[gets $gf line] >= 0} {
    incr lineno
    if { [ process_line $line ] != 0 } {
       set eline $g("Buginfo")
       tk_dialog .mv.error "Bad line" \
            "Bad line at line $lineno\n$eline\n$line" {}  0  "OK"
       close $gf
       exit 1
    }
  }

}

proc add_label { label } {
  global g
  
  set key "label $label"
  set nkey "labelnum $label"
  set add [ expr $g("iaddr") + 0 ]
  set addkey "addkey $add"

  if { [ catch { set g($key) } ] } {
    set g($nkey) $g("nlabels")
    set g($key) $add
    set g("nlabels") [ expr $g($nkey) + 1 ]
    if { $g($addkey) == "" } {
      set g($addkey) $label
    } else {
      set g($addkey) [ format "%s, %s" $g($addkey) $label ]
    }
  } else {
    set g("Buginfo") "Label defined twice"
    return -1 
  }
  return 0
}

proc add_global { global } {
  global g
  
  set key "global $global"
  if { [ catch { set g($key) } ] } {
    set gn $g("nglobals")
    set g($key) $gn
    set gkey "globalnum $gn"
    set g($gkey) $global
    set g("nglobals") [ expr $gn + 1 ]
  } else {
    set g("Buginfo") "Global defined twice"
    return -1 
  }
  return 0
}

proc process_line { line } {
  global g

  if { [ regexp "^\[^\/\]*" $line command ] } { 
    set line $command
  }
  if { [ regexp "^ *\(.*\[^ \]\) *$" $line newline command ] } {
    set line $command
  }

  # Comment line -- skip it

  if { [ regexp "^ *$" $line ] } {
    return 0

  # Label line

  } elseif { [ regexp "^\(\[a-zA-Z\]\[a-zA-Z0-9_\]*\):$" $line junk label ] } {
    return [ add_label $label ]

  # Global line

  } elseif { [ regexp "^\\.globl  *\(\[a-zA-Z\]\[a-zA-Z0-9_\]*\)$"  \
         $line junk global ] } {
    return [ add_global $global ]

  # ret line

  } elseif { [ regexp "^ret$" $line ] || \
             [ regexp "^noop$" $line ] } {
    add_line $line
    return 0

  # jsr/b

  } elseif { [ regexp "^b " $line ] || \
             [ regexp "^beq " $line ] || \
             [ regexp "^blt " $line ] || \
             [ regexp "^ble " $line ] || \
             [ regexp "^bgt " $line ] || \
             [ regexp "^bge " $line ] || \
             [ regexp "^jsr " $line ] || \
             [ regexp "^bne " $line ] } {
    if { [ regexp "^\(\[^ \]*\)  *(\[a-zA-Z\]\[a-zA-Z0-9_\]*\)$" $line junk \
        cmd label ] } {
      add_line "$cmd $label"
      return 0
    } else {
      set g("Buginfo") "Bad jsr/branch line"
      return -1
    }

  # pop line

  } elseif { [ regexp "^pop " $line ] } {
    if { [ regexp "^pop  *\(\[^ \]\[^ \]*\)$" $line junk arg1 ] } {
      if { [ regorval_spec $arg1 ] == 0 } {
        set g("Buginfo") "Bad pop line - wrong specification for arg1"
        return -1
      }
    } else {
      set g("Buginfo") "Bad pop line - wrong syntax"
      return -1
    }
    add_line "pop $arg1"
    return 0

  # push line

  } elseif { [ regexp "^push " $line ] } {
    if { [ regexp "^push  *\(\[^ \]\[^ \]*\)$" $line junk arg1 ] } {
      if { [ regorval_spec $arg1 ] == 0 } {
        set g("Buginfo") "Bad push line - wrong specification for arg1"
        return -1
      }
    } else {
      set g("Buginfo") "Bad push line - wrong syntax"
      return -1
    }
    add_line "push $arg1"
    return 0

  # St line

  } elseif { [ regexp "^st " $line ] } {
    if { [ regexp "^st  *\(\[^ \]\[^ \]*\) *-> *\(\[^ \]\[^ \]*\)$" $line \
         junk arg1 arg2 ] } {
      if { [ reg_spec $arg1 ] == 0 } {
        set g("Buginfo") "Bad st line - wrong specification for arg1"
        return -1
      }
      if { [ mem_spec $arg2 ] == 0 } {
        set g("Buginfo") "Bad st line - wrong specification for arg2"
        return -1
      }
    } else {
      set g("Buginfo") "Bad st line - wrong syntax"
      return -1
    }
    add_line "st $arg1 -> $arg2"
    return 0

  # Ld line

  } elseif { [ regexp "^ld " $line ] } {
    if { [ regexp "^ld  *\(\[^ \]\[^ \]*\) *-> *\(\[^ \]\[^ \]*\)$" $line \
         junk arg1 arg2 ] } {
      if { [ mem_spec $arg1 ] == 0 } {
        set g("Buginfo") "Bad ld line - wrong specification for arg1"
        return -1
      }
      if { [ reg_spec $arg2 ] == 0 || [ read_only_reg $arg2 ] == 1 } {
        set g("Buginfo") "Bad ld line - wrong specification for arg2"
        return -1
      }
    } else {
      set g("Buginfo") "Bad ld line - wrong syntax"
      return -1
    }
    add_line "ld $arg1 -> $arg2"
    return 0

  # Mov line

  } elseif { [ regexp "^mov " $line ] } {
    if { [ regexp "^mov  *\(\[^ \]\[^ \]*\) *-> *\(\[^ \]\[^ \]*\)$" $line \
         junk arg1 arg2 ] } {
      if { [ regorval_spec $arg1 ] == 0 } {
        set g("Buginfo") "Bad mov line - wrong specification for arg1"
        return -1
      }
      if { [ reg_spec $arg2 ] == 0 || [ read_only_reg $arg2 ] == 1 } {
        set g("Buginfo") "Bad mov line - wrong specification for arg2"
        return -1
      }
    } else {
      set g("Buginfo") "Bad mov line - wrong syntax"
      return -1
    }
    add_line "mov $arg1 -> $arg2"
    return 0

  # Arithmetic line

  } elseif { [ regexp "^add " $line ] || \
             [ regexp "^sub " $line ] || \
             [ regexp "^mul " $line ] || \
             [ regexp "^idiv " $line ] || \
             [ regexp "^imod " $line ] } {
    regexp "^\[^ \]*" $line cmd ] 
    if { [ regexp "^\[^ \]*  *\(\[^ \]\[^ \]*\), *\(\[^ \]\[^ \]*\) *-> *\(\[^ \]\[^ \]*\)$" \
         $line junk arg1 arg2 arg3 ] } {
      if { [ reg_spec $arg1 ] == 0 } {
        set g("Buginfo") "Bad $cmd line - wrong specification for arg1"
        return -1
      }
      if { [ reg_spec $arg2 ] == 0 } {
        set g("Buginfo") "Bad $cmd line - wrong specification for arg1"
        return -1
      }
      if { [ reg_spec $arg3 ] == 0 } {
        set g("Buginfo") "Bad $cmd line - wrong specification for arg3"
        return -1
      }
    } else {
      set g("Buginfo") "Bad $cmd line - wrong syntax"
      return -1
    }
    add_line "$cmd $arg1, $arg2 -> $arg3"
    return 0

  } elseif { [ regexp "^cmp " $line ] } { 
    if { [ regexp "^cmp  *\(\[^ \]\[^ \]*\), *\(\[^ \]\[^ \]*\)$" \
         $line junk arg1 arg2 ] } {
      if { [ reg_spec $arg1 ] == 0 } {
        set g("Buginfo") "Bad cmp line - wrong specification for arg1"
        return -1
      }
      if { [ reg_spec $arg2 ] == 0 } {
        set g("Buginfo") "Bad cmp line - wrong specification for arg1"
        return -1
      }
    } else {
      set g("Buginfo") "Bad cmp line - wrong syntax"
      return -1
    }
    add_line "cmp $arg1, $arg2"
    return 0

  } else {
    set g("Buginfo") "Unknown line"
    return -1
  }
  return -1
}

proc step { } {
  global g

  set g("stepno") [ expr $g("stepno") + 1 ]
  if { [ process_step ] != 0 } { 
    set eline $g("Buginfo")
    tk_dialog .mv.error "Error" "Execution error: $eline" {}  0  "OK"
    exit 1
  }

  redraw
}

proc get_regval { arg } {
  global g

  if { [ regexp "#\(.*\)" $arg junk val1 ] } {
    return $val1
  } elseif { [ regexp "%\(.*\)" $arg junk val1 ] } {
    return $g($val1)
  } else {
    tk_dialog .mv.error "get_regval -- bad arg $arg" \
              "get_regval -- bad arg $arg"  {}  0  "OK"
    exit 1
  }
}

proc get_reg { arg } {
  global g

  if { [ regexp "%\(.*\)" $arg junk val1 ] } {
    return $g($val1)
  } else {
    tk_dialog .mv.error "get_reg -- bad arg $arg" \
              "get_regval -- bad arg $arg"  {}  0  "OK"
    exit 1
  }
}

proc process_step { } {
  global g

  set reg "pc"
  set nextpc $g($reg)
  set gkey "addval $nextpc"
  incr nextpc 4
  set g($reg) $nextpc

  if { [ catch { set g($gkey) } ] } {
    set g("Buginfo") "Seg Fault on PC"
    return -1
  }
 
  set inst $g($gkey)

  # ret line

  if { [ regexp "^ret$" $inst ] } {
    set sp "sp"
    set fp "fp"
    set pc "pc"
    set addr [ expr $g($fp) + 4 ]
    set gkey "addval $addr"
    if { [ catch { set g($gkey) } ] } {
      set addr [ expr $g($fp) - 4 ]
      set gkey "addval $addr"
      if { [ catch { set g($gkey) } ] } {
        set g("Buginfo") "Ret -- seg fault"
        return -1
      } else {
        tk_dialog .mv.error "Program Finished" \
                  "Program Finished"  {}  0  "OK"
        exit 0
      }
    }
    set g($fp) $g($gkey)
    incr addr 4
    set gkey "addval $addr"
    if { [ catch { set g($gkey) } ] } {
      set g("Buginfo") "Ret -- seg fault"
      return -1
    }
    set g($pc) $g($gkey)
    set g($sp) $addr
    return 0

  } elseif { [ regexp "^noop$" $inst ] } {
    return 0

  # jsr/b

  } elseif { [ regexp "^b " $inst ] || \
             [ regexp "^beq " $inst ] || \
             [ regexp "^blt " $inst ] || \
             [ regexp "^ble " $inst ] || \
             [ regexp "^bgt " $inst ] || \
             [ regexp "^bge " $inst ] || \
             [ regexp "^jsr " $inst ] || \
             [ regexp "^bne " $inst ] } {
    if { [ regexp "^\(\[^ \]*\)  *(\[a-zA-Z\]\[a-zA-Z0-9_\]*\)$" $inst junk \
        cmd label ] } {
      set reg "pc"
      if { $cmd == "b" } {
        set lkey "label $label"
        set g($reg) $g($lkey)
        return 0
      } elseif { $cmd == "jsr" } {
        set reg2 "sp"
        set reg3 "fp"
        set address $g($reg2)
        set gkey "addval $address"
        set g($gkey) $nextpc
        incr address -4
        set gkey "addval $address"
        set g($gkey) $g($reg3)
#        tk_dialog .mv.error "Debug" [ format "0x%x" $g($gkey) ]  {}  0  "OK"
        incr address -4
        set g($reg2) $address 
        set g($reg3) $address 
        adjust_stacktos
        set lkey "label $label"
        set g($reg) $g($lkey)
        return 0
      } elseif { [ expr 1 + $g("lastcmp") ]  != $g("stepno") } {
        return 0
      } elseif { $cmd == "beq" && $g("csrval") == "Equal" || \
                 $cmd == "ble" && $g("csrval") != "Greater" || \
                 $cmd == "blt" && $g("csrval") == "Less" || \
                 $cmd == "bge" && $g("csrval") != "Less" || \
                 $cmd == "bgt" && $g("csrval") == "Greater" || \
                 $cmd == "bne" && $g("csrval") != "Equal" } {
        set lkey "label $label"
        set g($reg) $g($lkey)
        return 0
      } else { 
        return 0
      } 
    } else {
      set g("Buginfo") "Bad jsr/branch line"
      return -1
    }
  # Mov inst

  } elseif { [ regexp "^mov " $inst ] } {
    regexp "^mov  *\(\[^ \]\[^ \]*\) *-> *%\(\[^ \]\[^ \]*\)$" $inst \
       junk arg1 arg2 
    set val [ get_regval $arg1  ]
    set g($arg2) [ expr $val + 0 ]
    return 0

  # St inst

  } elseif { [ regexp "^st " $inst ] } {
    if { [ regexp "^st  *\(\[^ \]\[^ \]*\) *-> *\(\[^ \]\[^ \]*\)$" $inst \
         junk arg1 arg2 ] } {
      set arg [ get_reg $arg1 ]
      set address [ get_memaddr $arg2 ]
      set key "addval $address"
      if { [ catch { set g($key) } ] } {
        set g("Buginfo") "Bad st inst - invalid address"
        return -1
      }
      set g($key) $arg
      return 0
    } else {
      set g("Buginfo") "Bad st inst - wrong syntax"
      return -1
    }

  # ld inst

  } elseif { [ regexp "^ld " $inst ] } {
    if { [ regexp "^ld  *\(\[^ \]\[^ \]*\) *-> *%\(\[^ \]\[^ \]*\)$" $inst \
         junk arg1 arg2 ] } {
      set address [ get_memaddr $arg1 ]
      set key "addval $address"
      if { [ catch { set g($key) } ] } {
        set g("Buginfo") "Bad ld inst - invalid address"
        return -1
      }
      set g($arg2) $g($key)
      return 0
    } else {
      set g("Buginfo") "Bad ld inst - wrong syntax"
      return -1
    }

  # arithmetic inst

  } elseif { [ regexp "^add " $inst ] || \
             [ regexp "^sub " $inst ] || \
             [ regexp "^mul " $inst ] || \
             [ regexp "^idiv " $inst ] || \
             [ regexp "^imod " $inst ] } {
    regexp "^\[^ \]*" $inst cmd ] 
    if { [ regexp "^\[^ \]*  *\(\[^ \]\[^ \]*\), *\(\[^ \]\[^ \]*\) *-> *%\(\[^ \]\[^ \]*\)$" \
         $inst junk arg1 arg2 arg3 ] } {
      set arg1 [ get_reg $arg1 ]
      set arg2 [ get_reg $arg2 ]
    } else {
      set g("Buginfo") "Bad $cmd inst - wrong syntax"
      return -1
    }
    if { $cmd == "add" } {
      set g($arg3) [ expr $arg1 + $arg2 ]
    } elseif { $cmd == "sub" } {
      set g($arg3) [ expr $arg1 - $arg2 ]
    } elseif { $cmd == "mul" } {
      set g($arg3) [ expr $arg1 * $arg2 ]
    } elseif { $cmd == "idiv" } {
      set g($arg3) [ expr $arg1 / $arg2 ]
    } elseif { $cmd == "imod" } {
      set g($arg3) [ expr $arg1 % $arg2 ]
    } else {
      set g("Buginfo") "Bad $cmd inst - wrong syntax"
      return -1
    }
    return 0

  # arithmetic inst

  } elseif { [ regexp "^cmp " $inst ] } {
    if { [ regexp "^cmp  *\(\[^ \]\[^ \]*\), *\(\[^ \]\[^ \]*\)$" \
         $inst junk arg1 arg2 ] } {
      set arg1 [ get_reg $arg1 ]
      set arg2 [ get_reg $arg2 ]
      if { $arg1 == $arg2 } {
        set g("csrval") "Equal"
      } elseif { $arg1 > $arg2 } {
        set g("csrval") "Greater"
      } else {
        set g("csrval") "Less"
      }
      set g("lastcmp") $g("stepno")
    }
    return 0

  # pop inst

  } elseif { [ regexp "^pop " $inst ] } {
    if { [ regexp "^pop  *\(\[^ \]\[^ \]*\)$" $inst junk arg1 ] } {
      set arg1 [ get_regval $arg1 ]
      set reg "sp"
      set g($reg) [ expr $g($reg) + $arg1 ]
      return 0
    } else {
      set g("Buginfo") "bad pop"
      return -1
    }
  } elseif { [ regexp "^push " $inst ] } {
    if { [ regexp "^push  *\(\[^ \]\[^ \]*\)$" $inst junk arg1 ] } {
      set arg1 [ get_regval $arg1 ]
      set reg "sp"
      set g($reg) [ expr $g($reg) - $arg1 ]
      adjust_stacktos
      return 0
    } else {
      set g("Buginfo") "bad push"
      return -1
    }
  }

  set g("Buginfo") "$inst hmmm not implemented yet"
  return -1

  # pop inst

  if { [ regexp "^pop " $inst ] } {
    if { [ regexp "^pop  *\(\[^ \]\[^ \]*\)$" $inst junk arg1 ] } {
      if { [ regorval_spec $arg1 ] == 0 } {
        set g("Buginfo") "Bad pop inst - wrong specification for arg1"
        return -1
      }
    } else {
      set g("Buginfo") "Bad pop inst - wrong syntax"
      return -1
    }
    add_inst "pop $arg1"
    return 0

  # push inst

  } elseif { [ regexp "^push " $inst ] } {
    if { [ regexp "^push  *\(\[^ \]\[^ \]*\)$" $inst junk arg1 ] } {
      if { [ regorval_spec $arg1 ] == 0 } {
        set g("Buginfo") "Bad push inst - wrong specification for arg1"
        return -1
      }
    } else {
      set g("Buginfo") "Bad push inst - wrong syntax"
      return -1
    }
    add_inst "push $arg1"
    return 0


  # Ld inst

  } elseif { [ regexp "^ld " $inst ] } {
    if { [ regexp "^ld  *\(\[^ \]\[^ \]*\) *-> *\(\[^ \]\[^ \]*\)$" $inst \
         junk arg1 arg2 ] } {
      if { [ mem_spec $arg1 ] == 0 } {
        set g("Buginfo") "Bad ld inst - wrong specification for arg1"
        return -1
      }
      if { [ reg_spec $arg2 ] == 0 } {
        set g("Buginfo") "Bad ld inst - wrong specification for arg2"
        return -1
      }
    } else {
      set g("Buginfo") "Bad ld inst - wrong syntax"
      return -1
    }
    add_inst "ld $arg1 -> $arg2"
    return 0

  # arithmetic inst

  } elseif { [ regexp "^add " $inst ] || \
             [ regexp "^sub " $inst ] || \
             [ regexp "^mul " $inst ] || \
             [ regexp "^idiv " $inst ] || \
             [ regexp "^imod " $inst ] } {
    regexp "^\[^ \]*" $inst cmd ] 
    if { [ regexp "^\[^ \]*  *\(\[^ \]\[^ \]*\), *\(\[^ \]\[^ \]*\) *-> *\(\[^ \]\[^ \]*\)$" \
         $inst junk arg1 arg2 arg3 ] } {
      if { [ reg_spec $arg1 ] == 0 } {
        set g("Buginfo") "Bad $cmd inst - wrong specification for arg1"
        return -1
      }
      if { [ reg_spec $arg2 ] == 0 } {
        set g("Buginfo") "Bad $cmd inst - wrong specification for arg1"
        return -1
      }
      if { [ reg_spec $arg3 ] == 0 || [ read_only_reg $arg3 ] == 1 } {
        set g("Buginfo") "Bad $cmd inst - wrong specification for arg3"
        return -1
      }
    } else {
      set g("Buginfo") "Bad $cmd inst - wrong syntax"
      return -1
    }
    add_inst "$cmd $arg1, $arg2 -> $arg3"
    return 0

  } else {
    set g("Buginfo") "Unknown inst"
    return -1
  }
  return -1
}

proc adjust_stacktos { } {
  global g
  set reg "sp" 

  if { $g($reg) <= $g("stacktos") } {
    for { set i $g("stacktos") } { $i >= [ expr $g($reg) - 4 ] } { incr i -4 } {
      set gkey "addval $i"
      if { [ catch { set g($gkey) } ] } {
        set g($gkey) 0
      }
    }
    set g("stacktos") [ expr $g($reg) - 4 ]
  }
}

proc add_line { arg } {
  global g

  set inst [ expr $g("iaddr") + 0 ]
  set key "addval $inst"
  set g($key) $arg
  set g("iaddr") [ expr $inst + 4 ]
  set add [ expr $g("iaddr") + 0 ]
  set addkey "addkey $add"
  set g($addkey) ""
}
proc number_dec_spec { arg } {
  if { [ regexp "^\[-+\]\(.*\)" $arg junk remainder ] } {
    set arg $remainder
  }
  if { [ regexp "^\[0-9\]\[0-9\]*$" $arg ] } { 
    return 1
  } else {
    return 0
  }
}

proc number_hex_spec { arg } {
  if { [ regexp "^\[0-9a-fA-F\]\[0-9a-fA-F\]*$" $arg ] } { 
    return 1
  } else {
    return 0
  }
}

proc reg_spec { arg } {
  if { [ regexp "^%\(.*\)$" $arg junk regname ] } { 
    return [ reg_noparen_spec $regname ] 
  } else {
    return 0
  }
}

proc mem_spec { arg } {
  if { [ regexp "^\(\[a-zA-Z\]\[a-zA-Z0-9_\]*\)$" $arg ] } {
    return 1
  } elseif { $arg == "\[sp\]--" } {
    return 1
  } elseif { $arg == "++\[sp\]" } {
    return 1
  } elseif { [ regexp "^\\\[\(.*\)\\\]$" $arg junk inside ] } {
    if { [ reg_noparen_spec $inside ] } { return 1 } 
    if { [ regexp "^fp\[+-\]\(\[0-9\]\[0-9\]*\)$" $inside junk offset ] } {
      if { [ expr $offset % 4 ] == 0 } { return 1 }
    }
  } 
  return 0 
}

proc get_memaddr { arg } {
  global g 

  if { [ regexp "^\(\[a-zA-Z\]\[a-zA-Z0-9_\]*\)$" $arg junk arg] } {
    set key "global $arg"
    if { [ catch { set g($key) } ] } {
      tk_dialog .mv.error "get_memaddr -- bad arg $arg" \
                "get_memaddr -- bad arg $arg"  {}  0  "OK"
      exit 1
    }
    set gn $g($key)
    set gkey "globaladd $gn"
    return $g($gkey)
  } elseif { $arg == "\[sp\]--" } {
    set reg "sp"
    set addr $g($reg)
    set g($reg) [ expr $addr - 4 ]
    adjust_stacktos
    return $addr
  } elseif { $arg == "++\[sp\]" } {
    set reg "sp"
    set addr $g($reg)
    set g($reg) [ expr $addr + 4 ]
    set addr $g($reg)
    return $addr
  } elseif { [ regexp "^\\\[\(.*\)\\\]$" $arg junk inside ] } {
    if { [ reg_noparen_spec $inside ] } { return $g($inside) }
    if { [ regexp "^fp\(\[+-\]\[0-9\]\[0-9\]*\)$" $inside junk offset ] } {
      set reg "fp"
      return [ expr $g($reg) + $offset ]
    }
    tk_dialog .mv.error "get_memaddr -- bad arg $arg" \
              "get_memaddr -- bad arg $arg"  {}  0  "OK"
    exit 1
  } else {
    tk_dialog .mv.error "get_memaddr -- bad arg $arg" \
              "get_memaddr -- bad arg $arg"  {}  0  "OK"
    exit 1
  }
}

proc read_only_reg { arg } {
  if { $arg == "%g0" } { return 1 }
  if { $arg == "%g1" } { return 1 }
  if { $arg == "%gm1" } { return 1 }
  return 0
}

proc reg_noparen_spec { arg } {
  if { $arg == "sp" } { return 1 }
  if { $arg == "pc" } { return 1 }
  if { $arg == "fp" } { return 1 }
  if { $arg == "g0" } { return 1 }
  if { $arg == "g1" } { return 1 }
  if { $arg == "gm1" } { return 1 }
  if { [ regexp "^r\[0-7\]$" $arg ] } { return 1 }
  return 0
}

proc regorval_spec { arg } {
  if { [ regexp "^%\(.*\)$" $arg junk regname ] } { 
    return [ reg_noparen_spec $regname ] 
  } elseif { [ regexp "^#0\[Xx\]\(.*\)$" $arg junk num ] } { 
    return [ number_hex_spec $num ] 
  } elseif { [ regexp "^#\(.*\)$" $arg junk num ] } { 
    return [ number_dec_spec $num ] 
  } else {
    return 0
  }
}
  
  frame .mv
  wm title . "JASS -- CS360 Assembler"
  pack .mv
  global g

  set g("stackleft") 100
  set g("stacktop") 25
  set g("stackwidth") 120
  set g("regleft") 330
  set g("regtop") 25
  set g("regwidth") 120
  set g("regheight") 20
  set g("nrows") 20
  set g("nglobalrows") [ expr $g("nrows") - 10 ] 
  set g("codeleft") 590
  set g("codetop") 25
  set g("codewidth") 200

  set g("rowheight") 20
  set g("width") 880
  set g("height") [ expr $g("rowheight")*$g("nrows") + 2*$g("rowheight") ]
  
  canvas .mv.c  \
     -width $g("width")  -height $g("height") -background black
  pack .mv.c -side top

  frame .mv.buttons -background black -width $g("width") 

  frame .mv.buttons.scrollcode -background black 
  button .mv.buttons.scrollcode.down -text "Scroll Code Down" \
     -command scroll_code_down -foreground red -background black 
  button .mv.buttons.scrollcode.up -text "Scroll Code Up" \
     -command scroll_code_up -foreground red -background black 

  frame .mv.buttons.scrollstack -background black 
  button .mv.buttons.scrollstack.down -text "Scroll Stack Down" \
     -command scroll_stack_down -foreground red -background black 
  button .mv.buttons.scrollstack.up -text "Scroll Stack Up" \
     -command scroll_stack_up -foreground red -background black 

  frame .mv.buttons.height -background black
  label .mv.buttons.height.l -fg red -bg black -text "Window Height"
  scale .mv.buttons.height.scale -from 15 -to 40 -resolution 1 -length 100 \
        -orient horizontal  -width 5  -sliderlength 10 \
        -background black -fg red -highlightbackground black
  frame .mv.buttons.quit -background black
  button .mv.buttons.quit.redraw -text "Redraw" \
     -command redraw -foreground red -background black 
  button .mv.buttons.quit.quit -text Quit  -command exit \
    -foreground red -background black
  
  button .mv.buttons.step -text "Step" -command step \
    -foreground red -background black 
  frame .mv.buttons.anim  -background black 
  button .mv.buttons.anim.animate -text Animate  -command animate \
    -foreground red -background black
  button .mv.buttons.anim.animtoggle -text "Make Animation Fast" \
    -command animtoggle \
    -foreground red -background black
  button .mv.buttons.socket -text "Whatever" -command open_socket  \
    -foreground red -background black 
  entry .mv.buttons.host 

  pack .mv.buttons.step -side left -fill both -expand yes
  pack .mv.buttons.anim -side left -fill x -expand yes
  pack .mv.buttons.anim.animate -side top -fill x -expand yes
  pack .mv.buttons.anim.animtoggle -side bottom -fill x -expand yes
  pack .mv.buttons -side top -fill x -expand yes
  pack .mv.buttons.scrollstack -side left -fill x -expand yes
  pack .mv.buttons.scrollstack.up -side top -fill x -expand yes
  pack .mv.buttons.scrollstack.down -side bottom -fill x -expand yes
  pack .mv.buttons.scrollcode -side left -fill x -expand yes
  pack .mv.buttons.scrollcode.up -side top -fill x -expand yes
  pack .mv.buttons.scrollcode.down -side bottom -fill x -expand yes
  pack .mv.buttons.height -side left -fill x -expand yes
  pack .mv.buttons.height.l -side top -fill x -expand yes
  pack .mv.buttons.height.scale -side bottom -fill x -expand yes
  pack .mv.buttons.quit -side left -fill x -expand yes
  pack .mv.buttons.quit.redraw -side top -fill x -expand yes
  pack .mv.buttons.quit.quit -side bottom -fill x -expand yes
  
  .mv.buttons.height.scale set $g("nrows")

  set g("filename") "/"
  set g("nlabels") 0
  set g("iaddr") 0x1000
  set add [ expr $g("iaddr") + 0 ]
  set addkey "addkey $add"
  set g($addkey) ""

  set g("saddr") 0x1000
  set g("nglobals") 0
  set g("Buginfo") ""
  
  redraw

  if { $argc == 0 } {
    set f  [tk_getOpenFile -title "Open File" ]
    if { $f == "" } exit
  } else {
    set f [ lindex $argv 0 ]
  }
  
  read_file $f


  set key "label main"
  if { [ catch { set g($key) } ] } {
    tk_dialog .mv.error "Program Error" "No `main' specified" \
              {}  0  "OK"
    exit 1
  }

  for { set i 0 } { $i < 5 } { incr i } {
    set reg [ format "r%d" $i ]
    set g($reg) 0 
  }
  set reg "pc"
  set g($reg) [ expr $g($key) + 0 ]
  set reg "fp"
  set g($reg) 16774216
  set reg "sp"
  set g($reg) 16774216
  set reg "g0"
  set g($reg) 0
  set reg "g1"
  set g($reg) 1
  set reg "gm1"
  set g($reg) -1

  set g("firstcodedraw") $g("saddr")

  set gl $g("iaddr")
  if { [ expr $gl  % 4096 ] == 0 } {
    set $g("firstglobal") $gl
  } else {
    incr gl 4096
    set gl [ expr $gl - ( $gl % 4096 ) ]
  } 

  set g("firstglobal") 0

  for { set i 0 } { $i < $g("nglobals") } { incr i } {
    set address [ expr $gl + $i * 4 ]
    set gkey "globaladd $i"
    set g($gkey) $address
    set gkey "addval $address"
    set g($gkey) 0
  }

  set i 16774216
  set g("stackbase") $i
  set g("stackabsbottom") $i
  set gkey "addval $i"
  set g($gkey) 0

  incr i -4
  set gkey "addval $i"
  set g($gkey) 0

  incr i -4
  set gkey "addval $i"
  set g($gkey) 0

  incr i -4
  set g("stacktos") $i
  
  set g("stepno") 0
  set g("lastcmp") -2
  set g("csrval") "-"
  set g("animok") 1
  set g("animdelay") 1000

  redraw
