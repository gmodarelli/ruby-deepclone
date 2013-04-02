require 'rake'

require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new('spec') do |t|
  t.verbose = true
end

require 'rake/extensiontask'

def gemspec
  @clean_gemspec ||= eval(File.read(File.expand_path('../deep_clone.gemspec', __FILE__)))
end

Rake::ExtensionTask.new("deep_clone", gemspec) do |ext|
  ext.lib_dir = File.join 'lib', 'deep_clone'
end
Rake::Task[:spec].prerequisites << :compile
