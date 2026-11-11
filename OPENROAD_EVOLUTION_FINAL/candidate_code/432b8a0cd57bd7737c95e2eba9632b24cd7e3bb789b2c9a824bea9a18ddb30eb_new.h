// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07251950;
  double density_weight = 0.59560447;
  double prefix_weight = 0.01830740;
  double neighborhood_weight = 0.25457507;
  double late_weight = 0.24740978;
  double critical_weight = 0.49440394;
  unsigned budget = 31;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
