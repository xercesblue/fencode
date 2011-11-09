# Author: Francisco De La Cruz <dlcs.frank@gmail.com>
# Date: Nov 8, 2011
# Crude/Naive FEN array to algebraic notation converter for ruby 1.9.1

#NOTE: This code does not work with ruby < 1.9.1
require 'enumerator'

moves = []
CHAR='_'
FENS = ["rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0",
        "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1",
        "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2",
        "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"]
=begin
FENS = Array["rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0",
"rnbqkbnr/ppp1pppp/8/3p4/3P4/4P3/PPP2PPP/RNBQKBNR b KQkq - 0 2",
"rnbqkb1r/ppp1pppp/5n2/3p4/3P4/4P3/PPP2PPP/RNBQKBNR w KQkq - 1 2"]
=end

FENS.map! { |fen| fen[0,fen.index(/\s/)].split('/').each { |rank|
rank.gsub!(/\d/) {|d| CHAR*Integer(d)}}}.each_cons(2) { |a, b| rank=0
  a.zip(b).each do |ra, rb| 8.times {|file| ra_chr = ra[file]
      rb_chr = rb[file]
      act_rank = 8-rank
      act_file = (file+65).chr
      if ra_chr != rb_chr
	if ra_chr == CHAR
          if rb_chr.downcase == 'p'
            moves.push("#{act_file}#{act_rank}")
          else
            moves.push("#{rb_chr}#{act_file}#{act_rank}")
          end
	end
      end
    }
    rank+=1
  end
}
# Just print them, for now !
puts "==Generated Boards=="
puts FENS
puts "==Calculated Moves=="
puts moves
