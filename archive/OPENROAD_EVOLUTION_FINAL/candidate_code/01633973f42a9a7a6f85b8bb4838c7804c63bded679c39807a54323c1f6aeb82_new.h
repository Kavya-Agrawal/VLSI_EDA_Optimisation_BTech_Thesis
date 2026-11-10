// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.66313808;
  double density_weight = 0.45008317;
  double prefix_weight = 0.40588106;
  double neighborhood_weight = 0.36799903;
  double late_weight = 0.25604994;
  double critical_weight = 0.24271145;
  unsigned budget = 24;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
