#!/usr/bin/env perl

use strict;
use warnings;
use utf8;

=pod

=head1 SYNOPSIS

  perl gen_gradient.pl 190 255 255 230 255 255

=head1 DESCRIPTION

This script generates hsv gradients for the Kyria v1.x underglow 

=cut

my @dist = (0,2.7,5.7,4.8,8,12.1,10.3,8.2,12.1,13.5);

my ($hf, $sf, $vf, $ht, $st, $vt) = @ARGV;

for my $i (0..(2*$#dist+1)) {
    my $j = $i % ($#dist+1);
    my $h = $hf + ($ht - $hf) * $dist[$j] / $dist[-1];
    my $s = $sf + ($st - $sf) * $dist[$j] / $dist[-1];
    my $v = $vf + ($vt - $vf) * $dist[$j] / $dist[-1];
    printf "    { %i, %i, %i, %i, %i },\n",
        $i, 1, $h, $s, $v;
}





