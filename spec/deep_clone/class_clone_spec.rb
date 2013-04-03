require 'spec_helper'

class Bar
  attr_accessor :a, :b, :c
  def initialize
    @a = [ Time.new, 123, "foo" ]
    @b = { a: 1, b: Time.new, c: [ 1, 2, "foo" ] }
    @c = nil
  end
end

class Foo
  attr_accessor :a, :b, :c, :d, :e
  def initialize
    @a = [ Time.new, Time.new ]
    @b = "foo"
    @c ={"a" => 1, "b" => 2, "c" => 3}
    @d = "dfgdfhf"
    @e = Bar.new
  end
end


describe DeepClone do
  describe '.clone' do
    it 'should clone a class' do
      f1 = Foo.new
      f2 = DeepClone.clone(f1)

      f2.c["d"] = 4

      # Object
      expect(f1).to_not       eql(f2)

      # Hash
      expect(f1.c).to_not     eql(f2.c)
      expect(f1.c["d"]).to    be_nil
      expect(f1.c["a"]).to    eql(f2.c["a"])

      # Array
      expect(f1.a.object_id).to_not       eql(f2.a.object_id)
      expect(f1.a[0]).to                  eq(f2.a[0])
      expect(f1.a[0].object_id).to_not    eql(f2.a[0].object_id)

      # Instance
      expect(f1.e.object_id).to_not       eql(f2.e.object_id)
      expect(f1.e.a).to                   eq(f2.e.a)
      expect(f1.e.a[0].object_id).to_not  eql(f2.e.a[0].object_id)

      # Make sure they don't point to one another
      f1.e.a[3] = :bar
      f2.c["d"] = 4

      expect(f2.e.a[3]).to be_nil
      expect(f1.c["d"]).to be_nil
    end
  end
end
