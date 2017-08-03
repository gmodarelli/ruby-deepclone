# Deep Clone

## Status

|System|Status|
|--|--|
| Travis | [![Travis Build Status](https://travis-ci.org/gmodarelli/ruby-deepclone.svg?branch=master)](https://travis-ci.org/gmodarelli/ruby-deepclone) |
| Gem Version | [![Gem Version](https://badge.fury.io/rb/deep_clone.svg)](https://badge.fury.io/rb/deep_clone) |

## Description

This gem provides a native implementation to deep clone Ruby objects.
It supports Ruby 1.9.3, 2.2.x, 2.3.x and 2.4.x.

## Installation

```
gem install ruby_deep_clone
```

or add it to your `Gemfile`

```
gem 'ruby_deep_clone'
```

and run `bundle install`

## Usage

Can be used as follows:

```
require 'deep_clone'

object = Object.new
clone_object = DeepClone.clone obj
```
