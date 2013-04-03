$LOAD_PATH.unshift File.expand_path(File.dirname(__FILE__) + '/../lib')

require 'deep_clone'
require 'benchmark'

number_of = 10000

class Foo
  attr_accessor :a, :b, :c, :d
  def initialize()
    @a = [Time.new(),Time.new()]
    @b = "foo"
    @c ={"a" => 1, "b" => 2, "c" => 3}
    @d = "dfgdfhf"
  end
end

foo = Foo.new

Benchmark.bmbm do |x|
  x.report 'DeepClone' do
    number_of.times do
      bar = DeepClone.clone foo
    end
  end

  x.report 'Marshal dump/load' do
    number_of.times do
      bar = Marshal.load(Marshal.dump(foo))
    end
  end
end
