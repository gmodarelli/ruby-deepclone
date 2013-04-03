require 'spec_helper'

describe DeepClone do
  describe '.clone' do
    it 'should clone an integer' do
      # Integers aren't "deep cloned, so their object ID should remaiin the
      # same.
      i1 = 1
      i2 = DeepClone.clone i1

      expect(i1).to eql(i2)
    end

    it 'should clone a string' do
      s1 = "Ruby is awesome!"
      s2 = DeepClone.clone s1

      expect(s1).to     eq(s2)
      expect(s1).to_not eql(s2.object_id)
    end
  end
end
