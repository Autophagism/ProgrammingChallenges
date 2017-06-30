def win(player)
  if player == 2
    puts 'Oh no, a draw!'
    exit
  end

  puts "Player #{player + 1} wins!"
  exit
end

hand = [[], []]
ransom = []

if ARGV.empty?
  pool = (1..52).to_a

  until pool.length.zero?
    hand[pool.length % 2].push(pool.delete_at(rand(0...pool.length)) % 13)
  end
else
  pool = ARGV[0].split

  pool[0...26].each do |i|
    hand[0].push i
  end
  pool[26...52].each do |i|
    hand[1].push i
  end
end

until hand[0].length.zero? || hand[1].length.zero?
  if hand[0].first == hand[1].first
    3.times do
      win 2 if hand[0].first.nil? && hand[1].first.nil?
      win 1 if hand[0].first.nil?
      win 0 if hand[1].first.nil?

      ransom.push hand[0].shift
      ransom.push hand[1].shift
    end
  else
    (0..1).each do |i|
      if hand[1 - i].first > hand[i].first
        hand[1 - i].push ransom
        hand[1 - i].push hand[i - 1].shift
        hand[1 - i].push hand[i].shift
        hand[1 - i].flatten!
        ransom.clear
        break
      end
    end
  end
end

(0..1).each { |i| win i if hand[1 - i].length.zero? }
