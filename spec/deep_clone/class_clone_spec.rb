require 'spec_helper'

class Foo
  attr_accessor :a, :b, :c, :d
  def initialize()
    @a = [Time.new(),Time.new()]
    @b = "foo"
    @c ={"a" => 1, "b" => 2, "c" => 3}
    @d = "dfgdfhf"
  end
end

describe DeepClone do
  describe '.clone' do
    it 'should clone a class' do
      f1 = Foo.new
      f2 = DeepClone.clone(f1)

      # Object
      expect(f1).to_not       eql(f2)

      # Hash
      expect(f1.c).to_not     eql(f2.c)
      expect(f1.c["a"]).to    eql(f2.c["a"])

      # Array
      expect(f1.a).to_not     eql(f2.a)
      expect(f1.a[0]).to      eq(f2.a[0])
      expect(f1.a[0]).to_not  eql(f2.a[0])
    end
  end
end
