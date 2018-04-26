
proc do_read { } {
  global g

  if { ! [ gets stdin line ] } {
    return
  }

  if { $g("print") == "yes" } {
    puts $line
  }

  if { [ regexp "^.*Philosopher \(\[0-9\]*\) Thinking.*$" $line junk phil ] } {
    if { [ expr $phil < 0 || $phil >= $g("np") ] } {
      puts "Bad philosopher number: $line"
      exit 1
    }
    .mv.c itemconfigure [ .mv.c find withtag "phil$phil" ] -fill yellow
  } elseif { $line == "NOPRINT" } {
    set g("print") no
  } elseif { [ regexp "^.*Philosopher \(\[0-9\]*\) Picked Up Stick \(\[0-9\]*\).*$" $line junk phil  stick] } {
    set phil [ expr ( $phil + $g("np") - 1 ) % $g("np") ]
    set stick [ expr ( $stick + $g("np") - 1 ) % $g("np") ]
    .mv.c itemconfigure [ .mv.c find withtag "stick$stick:$phil" ] -fill red
    .mv.c itemconfigure [ .mv.c find withtag "unstick$stick" ] -fill white
  } elseif { [ regexp "^.*Philosopher \(\[0-9\]*\) Put Down Stick \(\[0-9\]*\).*$" $line junk phil  stick] } {
    set phil [ expr ( $phil + $g("np") - 1 ) % $g("np") ]
    set stick [ expr ( $stick + $g("np") - 1 ) % $g("np") ]
    .mv.c itemconfigure [ .mv.c find withtag "stick$stick:$phil" ] -fill white
    .mv.c itemconfigure [ .mv.c find withtag "unstick$stick" ] -fill black
  } elseif { [ regexp "^.*Philosopher \(\[0-9\]*\) Eating .*$" $line junk phil ] } {
    if { [ expr $phil < 0 || $phil >= $g("np") ] } {
      puts "Bad philosopher number: $line"
      exit 1
    }
    .mv.c itemconfigure [ .mv.c find withtag "phil$phil" ] -fill cyan

  } elseif { [ regexp "^.*Philosopher \(\[0-9\]*\) Hungry.*$" $line junk phil ] } {
    if { [ expr $phil < 0 || $phil >= $g("np") ] } {
      puts "Bad philosopher number: $line"
      exit 1
    }
    .mv.c itemconfigure [ .mv.c find withtag "phil$phil" ] -fill red
  }
  after 1 do_read
}
  
  frame .mv
  wm title . "Dining Philosophers"
  pack .mv
  global g

  set g("time") 0
  set g("width") 600
  set g("height") 600
  set g("tableradius") 200
  set g("philradius") 40
  set g("philrealradius") 32
  set g("print") "yes"
  
  canvas .mv.c  \
     -width $g("width")  -height $g("height") -background darkslategray
  pack .mv.c -side top

  set l [ expr ( $g("width") - $g("tableradius") * 2 ) / 2 ]
  set r [ expr $g("width") - $l ]
  .mv.c create oval $l $l $r $r -fill white  -outline black -width 6

  gets stdin line
  
  if { $line == "NOPRINT" } {
    set g("print") "no"
    gets stdin line
  }

  if { [ scan $line "#-Philosophers: %d" nphil ] } {
    set g("np") $nphil
    puts $line
  } else {
    puts "Error -- first line should be '#-Philosophers: n'"
    exit 1
  }

  set pi [ expr acos(-1) ]

  for { set num 0 } { $num < $g("np") } { incr num } {

    set angle [ expr $num * 360 / $g("np") + 90 ]
    set parad [ expr $angle * $pi / 180.0 ]
    set x [ expr $g("width") / 2 - cos($parad) * ( $g("tableradius") + $g("philradius") ) ]
    set y [ expr $g("height") / 2 - sin($parad) * ( $g("tableradius") + $g("philradius") ) ]
    set xs [ expr $g("width") / 2 - cos($parad) * ( $g("tableradius") * .65 ) ]
    set ys [ expr $g("height") / 2 - sin($parad) * ( $g("tableradius") * .65 ) ]
    set key "x$num"
    set g($key) $xs
    set key "y$num"
    set g($key) $ys

    .mv.c create oval [ expr $x - $g("philrealradius") ] \
                      [ expr $y - $g("philrealradius") ] \
                      [ expr $x + $g("philrealradius") ] \
                      [ expr $y + $g("philrealradius") ] \
         -fill yellow -outline black -width 3 -tag "phil$num"

  }
  
  for { set num 0 } { $num < $g("np") } { incr num } {
    set angle [ expr ( ( $num + 0.5) * 360 ) / $g("np") + 90 ]
    set arad [ expr $angle * $pi / 180 ]
    set xl [ expr $g("width") / 2 - cos($arad) * ( $g("tableradius") * 0.2 ) ]
    set yl [ expr $g("height") / 2 - sin($arad) * ( $g("tableradius") * 0.2 ) ]
    set xh [ expr $g("width") / 2 - cos($arad) * ( $g("tableradius") * 0.7 ) ]
    set yh [ expr $g("height") / 2 - sin($arad) * ( $g("tableradius") * 0.7 ) ]
 
    .mv.c create line $xl $yl $xh $yh \
         -fill black -width 3 -tag "unstick$num"

    set np [ expr ( $num + $g("np")-1 ) % $g("np") ]

    set key "x$num"
    set xs $g($key)
    set key "y$num"
    set ys $g($key)

    .mv.c create line $xl $yl $xs $ys \
         -fill white -width 3 -tag "stick$num:$np"

    set np [ expr ( $num + 1 ) % $g("np") ]
    set key "x$np"
    set xs $g($key)
    set key "y$np"
    set ys $g($key)

    .mv.c create line $xl $yl $xs $ys \
         -fill white -width 3 -tag "stick$num:$num"

  }


  after 1 do_read
