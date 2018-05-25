// Copyright 2017 The VGC Developers
// See the COPYRIGHT file at the top-level directory of this distribution
// and at https://github.com/vgc/vgc/blob/master/COPYRIGHT
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <vgc/dom/value.h>

namespace vgc {
namespace dom {

const Value& Value::invalid()
{
    // trusty leaky singleton
    static const Value* v = new Value();
    return *v;
}

void Value::unset()
{
    switch (type()) {
    case ValueType::DoubleArray:
        doubleArray_.clear();
        break;
    case ValueType::Vec2dArray:
        vec2dArray_.clear();
        break;
    default:
        // nothing
        break;
    }
    type_ = ValueType::Invalid;
}

void Value::shrinkToFit()
{
    // Note: it is possible that several vectors have unused capacity, which is
    // why we can't just shrinkToFit the current type(), but have to shrinkToFit
    // all of them.
    //
    // Example:
    // Value v;
    // v.set(Vec2dArray({{12, 10}, {23, 42}}));
    // v.set(DoubleArray({1, 2, 3})); // doesn't shrink vec2dArray_;
    //

    vec2dArray_.shrinkToFit();
    doubleArray_.shrinkToFit();
}

std::string toString(const Value& v)
{
    switch (v.type()) {
    case ValueType::Invalid:
        return "invalid_value";
    case ValueType::Color:
        return "color"; // XXX TODO
    case ValueType::DoubleArray:
        return toString(v.getDoubleArray());
    case ValueType::Vec2dArray:
        return toString(v.getVec2dArray());
    }
}

} // namespace dom
} // namespace vgc