// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95697795;
  double density_weight = 0.45945756;
  double prefix_weight = 0.45537643;
  double neighborhood_weight = 0.24780238;
  double late_weight = 0.07363763;
  double critical_weight = 0.40388687;
  unsigned budget = 4;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
