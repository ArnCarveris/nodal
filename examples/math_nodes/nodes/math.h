/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Fabio Massaioli
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __NODAL_EXAMPLE_MATH_NODES_MATH_NODE_H__
#define __NODAL_EXAMPLE_MATH_NODES_MATH_NODE_H__

#include "../node.h"

class math_node : public node
{
public:
  enum function
  {
    first,
    second,
    min,
    max,
    add,
    sub,
    mul,
    div,
    pow
  };

  struct input_data_t
  {
    double first;
    double second;
  };

  struct output_data_t
  {
    double result;
  };

  struct property_data_t
  {
    function fn;
  };

  std::size_t input_count() const override { return 2; }
  std::size_t output_count() const override { return 1; }
  std::size_t property_count() const override { return 1; }

  nodal::node_data* input_data() const override;
  nodal::node_data* property_data() const override;

  node_fn compile(nodal::node_data* property_data) const override;
};

#endif /* __NODAL_EXAMPLE_MATH_NODES_MATH_NODE_H__ */