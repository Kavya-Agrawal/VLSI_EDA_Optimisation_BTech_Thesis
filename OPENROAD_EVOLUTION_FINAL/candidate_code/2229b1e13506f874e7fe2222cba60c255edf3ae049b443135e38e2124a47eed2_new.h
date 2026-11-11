// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84286047;
  double density_weight = 0.00252063;
  double prefix_weight = 0.16460657;
  double neighborhood_weight = 0.39081232;
  double late_weight = 0.21059821;
  double critical_weight = 0.02956721;
  unsigned budget = 31;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
