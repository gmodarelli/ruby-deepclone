require 'spec_helper'

describe DeepClone do
  describe '.clone' do
    it 'should clone an instance of Time' do
      t1 = Time.new
      t2 = DeepClone.clone t1

      expect(t1).to eq(t2)
      expect(t1.object_id).to_not eq(t2.object_id)
    end

    it 'should clone an instance of Array' do
      a1 = [1, 2, 3, 4, 5, "a", "b", :c]
      a2 = DeepClone.clone a1

      expect(a1).to eq(a2)
      expect(a1.object_id).to_not     eq(a2.object_id)
      expect(a1[5].object_id).to_not  eq(a2[5].object_id)
    end

    it 'should clone an instance of a frozen Array' do
      a1 = [1, 2, 3, 4, 5, "a", "b", :c].freeze
      a2 = DeepClone.clone a1

      expect(a1).to eq(a2)
      expect(a1.object_id).to_not     eq(a2.object_id)
      expect(a1[5].object_id).to_not  eq(a2[5].object_id)
    end

    it 'should clone an instance of a Hash' do
      h1 = {a: 1, b: "foo", c: Time.new}
      h2 = DeepClone.clone h1

      expect(h1).to eq(h2)
      expect(h1.object_id).to_not     eq(h2.object_id)
      expect(h1[:b].object_id).to_not eq(h2[:b].object_id)
      expect(h1[:c].object_id).to_not eq(h2[:c].object_id)
    end

    it 'should clone an instance of Set' do
      s1 = Set.new
      [1, 2, 'foo', :bar].each do |elm|
        s1.add elm
      end
      s1.freeze

      s2 = DeepClone.clone s1

      expect(s1.object_id).to_not eq(s2.object_id)
    end
  end
end

