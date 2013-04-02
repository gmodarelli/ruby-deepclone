Gem::Specification.new do |s|
  s.specification_version = 2 if s.respond_to? :specification_version=
  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.rubygems_version = '1.3.5'

  s.name = 'deep_clone'
  s.version = '0.0.2'
  s.date = '2011-10-13'
  
  s.summary = "Ruby native deep clone"
  s.description = "Native implementation to create deep clones of Ruby objects"

  s.authors = ["Matthias Balmer"]
  s.email = 'balmma@sysinf.ch'
 
  s.extensions = ["ext/deep_clone/extconf.rb"]

  s.require_paths = ["ext", "lib"]

  s.files = ["deep_clone.gemspec","lib/deep_clone.rb","ext/deep_clone/deep_clone.c","ext/deep_clone/extconf.rb"]

  s.add_development_dependency 'rspec', '~> 2.13.0'
end
