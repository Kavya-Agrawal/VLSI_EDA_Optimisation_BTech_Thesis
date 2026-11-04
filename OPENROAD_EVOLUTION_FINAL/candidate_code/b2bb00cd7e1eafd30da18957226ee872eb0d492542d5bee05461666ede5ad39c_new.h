// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.06554471;
  double density_weight = 0.49323736;
  double prefix_weight = 0.34049904;
  double neighborhood_weight = 0.38529435;
  double late_weight = 0.06741200;
  double critical_weight = 0.43326418;
  unsigned budget = 19;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
