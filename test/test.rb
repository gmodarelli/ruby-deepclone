require "ext/deep_clone/deep_clone"

class Foo
  attr_accessor :a, :b, :c, :d 
  def initialize()
      @a = [Time.new(),Time.new()]
      @b = "foo"
      @c ={"a" => 1, "b" => 2, "c" => 3}
      @d = "dfgdfhf"
   end
end

time1 = Foo.new()

time2 = DeepClone.clone(time1)

puts ""
puts time1.a.inspect
puts time2.a.inspect

puts time1.c.inspect
puts time2.c.inspect

puts time1.d.object_id
puts time2.d.object_id

class Rec
 attr_accessor :ref
end

rec1 = Rec.new()
rec2 = Rec.new()

rec1.ref = rec2
rec2.ref = rec1

rec3 = DeepClone.clone(rec1)
puts rec3.inspect


