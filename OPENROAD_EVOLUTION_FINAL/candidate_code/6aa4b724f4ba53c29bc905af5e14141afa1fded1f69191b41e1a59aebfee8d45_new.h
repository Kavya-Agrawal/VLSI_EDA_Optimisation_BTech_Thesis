// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48028322;
  double density_weight = 0.36337904;
  double prefix_weight = 0.23476145;
  double neighborhood_weight = 0.01992637;
  double late_weight = 0.10133682;
  double critical_weight = 0.01382496;
  unsigned budget = 40;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
