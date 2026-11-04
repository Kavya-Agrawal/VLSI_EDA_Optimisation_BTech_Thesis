// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85632397;
  double density_weight = 0.03681899;
  double prefix_weight = 0.32510853;
  double neighborhood_weight = 0.30782606;
  double late_weight = 0.01978848;
  double critical_weight = 0.08024839;
  unsigned budget = 27;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
